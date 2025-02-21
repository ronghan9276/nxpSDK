/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

/* File modified by NXP. Changes are described in file
   /middleware/eiq/tensorflow-lite/readme.txt in section "Release notes" */

#include "tensorflow/lite/kernels/internal/reference/reduce.h"

#include <stddef.h>

#include <string.h>
#include <cstdint>
#include <limits>

#include "ruy/profiler/instrumentation.h"  // from @ruy
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/cpu_backend_context.h"
#include "tensorflow/lite/kernels/internal/compatibility.h"
#include "tensorflow/lite/kernels/internal/optimized/integer_ops/mean.h"
#include "tensorflow/lite/kernels/internal/optimized/neon_check.h"
#include "tensorflow/lite/kernels/internal/optimized/optimized_ops.h"
#include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/reference/integer_ops/mean.h"
#include "tensorflow/lite/kernels/internal/reference/reference_ops.h"
#include "tensorflow/lite/kernels/internal/tensor.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/internal/types.h"
#include "tensorflow/lite/kernels/kernel_util.h"

namespace tflite {
namespace ops {
namespace builtin {
namespace reduce {

// This file has reference implementation of reduce_* operators.
enum KernelType {
  kReference,
  kGenericOptimized,
};

struct OpData {
  int32_t multiplier;
  int shift;
  // The index of the temporary tensor where the quantized inputs are cached.
  int scratch_tensor_index;
};

struct OpContext {
  OpContext(TfLiteContext* context, TfLiteNode* node) {
    params = reinterpret_cast<TfLiteReducerParams*>(node->builtin_data);
    input = GetInput(context, node, 0);
    axis = GetInput(context, node, 1);
    output = GetOutput(context, node, 0);
  }
  TfLiteReducerParams* params;
  const TfLiteTensor* input;
  const TfLiteTensor* axis;
  TfLiteTensor* output;
};

void* Init(TfLiteContext* context, const char* buffer, size_t length) {
  // Creates two temp tensors to store index and axis for internal
  // implementation only.
  auto* op_data = new OpData();
  context->AddTensors(context, 3, &op_data->scratch_tensor_index);
  return op_data;
}

void Free(TfLiteContext* context, void* buffer) {
  delete reinterpret_cast<OpData*>(buffer);
}

// Resizes the temp tensor that stores resolved axis.
TfLiteStatus ResizeTempAxis(TfLiteContext* context, OpContext* op_context,
                            TfLiteTensor* resolved_axis) {
  TfLiteIntArray* axis_size = TfLiteIntArrayCreate(1);
  axis_size->data[0] = static_cast<int>(NumElements(op_context->axis));
  return context->ResizeTensor(context, resolved_axis, axis_size);
}

// Resizes the temp tensor that stores temp sum of reduced elements.
TfLiteStatus ResizeTempSum(TfLiteContext* context, OpContext* op_context,
                           TfLiteTensor* temp_sum) {
  TfLiteIntArray* size = TfLiteIntArrayCreate(1);
  size->data[0] = static_cast<int>(NumElements(op_context->output));
  return context->ResizeTensor(context, temp_sum, size);
}

// Resizes output array based on the input size and resolved axis.
TfLiteStatus ResizeOutputTensor(TfLiteContext* context, OpContext* op_context) {
  size_t num_axis = NumElements(op_context->axis);
  const TfLiteIntArray* input_dims = op_context->input->dims;
  int input_num_dims = NumDimensions(op_context->input);
  if (input_num_dims == 0) {
    return context->ResizeTensor(context, op_context->output,
                                 TfLiteIntArrayCreate(0));
  }
  const int* axis = GetTensorData<int>(op_context->axis);
  if (op_context->params->keep_dims) {
    TfLiteIntArray* output_dims = TfLiteIntArrayCreate(input_num_dims);
    for (int idx = 0; idx < input_num_dims; ++idx) {
      bool is_axis = false;
      for (int axis_idx = 0; axis_idx < num_axis; ++axis_idx) {
        if (axis[axis_idx] == idx || axis[axis_idx] + input_num_dims == idx) {
          is_axis = true;
          break;
        }
      }
      if (is_axis) {
        output_dims->data[idx] = 1;
      } else {
        output_dims->data[idx] = input_dims->data[idx];
      }
    }
    return context->ResizeTensor(context, op_context->output, output_dims);
  } else {
    // Calculates size of reducing axis.
    int num_reduce_axis = num_axis;
    for (int i = 0; i < num_axis; ++i) {
      int current = axis[i];
      if (current < 0) {
        current += input_num_dims;
      }
      TF_LITE_ENSURE(context, current >= 0 && current < input_num_dims);
      for (int j = 0; j < i; ++j) {
        int previous = axis[j];
        if (previous < 0) {
          previous += input_num_dims;
        }
        if (current == previous) {
          --num_reduce_axis;
          break;
        }
      }
    }
    // Determines output dimensions.
    TfLiteIntArray* output_dims =
        TfLiteIntArrayCreate(input_num_dims - num_reduce_axis);
    int num_skip_axis = 0;
    for (int idx = 0; idx < input_num_dims; ++idx) {
      bool is_axis = false;
      for (int axis_idx = 0; axis_idx < num_axis; ++axis_idx) {
        if (axis[axis_idx] == idx || axis[axis_idx] + input_num_dims == idx) {
          ++num_skip_axis;
          is_axis = true;
          break;
        }
      }
      if (!is_axis) {
        output_dims->data[idx - num_skip_axis] = input_dims->data[idx];
      }
    }
    return context->ResizeTensor(context, op_context->output, output_dims);
  }
}

// Initializes temp tensors to store index and resolved axis.
TfLiteStatus InitializeTemporaries(TfLiteContext* context, TfLiteNode* node,
                                   OpContext* op_context) {
  // Creates a temp index to iterate through input data.
  OpData* op_data = reinterpret_cast<OpData*>(node->user_data);
  TfLiteIntArrayFree(node->temporaries);
  node->temporaries = TfLiteIntArrayCreate(3);
  node->temporaries->data[0] = op_data->scratch_tensor_index;
  TfLiteTensor* scratch_tensor = GetTemporary(context, node, /*index=*/0);
  scratch_tensor->type = kTfLiteInt32;
  scratch_tensor->allocation_type = kTfLiteArenaRw;
  TfLiteIntArray* index_size = TfLiteIntArrayCreate(1);
  index_size->data[0] = NumDimensions(op_context->input);
  TF_LITE_ENSURE_OK(context,
                    context->ResizeTensor(context, scratch_tensor, index_size));

  // Creates a temp tensor to store resolved axis given input data.
  node->temporaries->data[1] = op_data->scratch_tensor_index + 1;
  TfLiteTensor* resolved_axis = GetTemporary(context, node, /*index=*/1);
  resolved_axis->type = kTfLiteInt32;
  // Creates a temp tensor to store temp sums when calculating mean.
  node->temporaries->data[2] = op_data->scratch_tensor_index + 2;
  TfLiteTensor* temp_sum = GetTemporary(context, node, /*index=*/2);
  switch (op_context->input->type) {
    case kTfLiteFloat32:
      temp_sum->type = kTfLiteFloat32;
      break;
    case kTfLiteInt32:
      temp_sum->type = kTfLiteInt64;
      break;
    case kTfLiteInt64:
      temp_sum->type = kTfLiteInt64;
      break;
    case kTfLiteUInt8:
      temp_sum->type = kTfLiteInt32;
      break;
    case kTfLiteInt8:
      temp_sum->type = kTfLiteInt32;
      break;
    case kTfLiteBool:
      temp_sum->type = kTfLiteBool;
      break;
    default:
      return kTfLiteError;
  }
  return kTfLiteOk;
}

TfLiteStatus PrepareSimple(TfLiteContext* context, TfLiteNode* node) {
  TF_LITE_ENSURE_EQ(context, NumInputs(node), 2);
  TF_LITE_ENSURE_EQ(context, NumOutputs(node), 1);

  OpContext op_context(context, node);
  TF_LITE_ENSURE_TYPES_EQ(context, op_context.axis->type, kTfLiteInt32);
  TF_LITE_ENSURE_OK(context, InitializeTemporaries(context, node, &op_context));

  TfLiteTensor* resolved_axis = GetTemporary(context, node, /*index=*/1);
  // Leaves work to Eval if axis is not constant; else resizes output.
  if (!IsConstantTensor(op_context.axis)) {
    SetTensorToDynamic(op_context.output);
    SetTensorToDynamic(resolved_axis);
    return kTfLiteOk;
  }
  resolved_axis->allocation_type = kTfLiteArenaRw;
  TF_LITE_ENSURE_OK(context,
                    ResizeTempAxis(context, &op_context, resolved_axis));
  TF_LITE_ENSURE_OK(context, ResizeOutputTensor(context, &op_context));
  return kTfLiteOk;
}

TfLiteStatus PrepareAny(TfLiteContext* context, TfLiteNode* node) {
  TF_LITE_ENSURE_EQ(context, NumInputs(node), 2);
  const TfLiteTensor* input = GetInput(context, node, 0);
  TF_LITE_ENSURE_TYPES_EQ(context, input->type, kTfLiteBool);
  return PrepareSimple(context, node);
}

TfLiteStatus PrepareMeanOrSum(TfLiteContext* context, TfLiteNode* node) {
  TF_LITE_ENSURE_OK(context, PrepareSimple(context, node));
  OpData* data = reinterpret_cast<OpData*>(node->user_data);

  // reduce_mean requires a buffer to store intermediate sum result.
  OpContext op_context(context, node);
  if (op_context.input->type == kTfLiteInt8) {
    const double real_multiplier =
        static_cast<double>(op_context.input->params.scale) /
        static_cast<double>(op_context.output->params.scale);
    int32_t exponent;
    QuantizeMultiplier(real_multiplier, &data->multiplier, &exponent);
    data->shift = exponent;
  }
  TfLiteTensor* temp_sum = GetTemporary(context, node, /*index=*/2);
  if (!IsConstantTensor(op_context.axis)) {
    SetTensorToDynamic(temp_sum);
    return kTfLiteOk;
  }
  temp_sum->allocation_type = kTfLiteArenaRw;
  return ResizeTempSum(context, &op_context, temp_sum);
}

void ResolveAxis(const int* axis_data, int axis_count,
                 tflite::MeanParams* op_params) {
  int i = 0;
  for (; i < axis_count; ++i) {
    op_params->axis[i] = static_cast<int16>(axis_data[i]);
  }
  for (; i < 4; ++i) {
    op_params->axis[i] = 1;
  }
}

template <KernelType kernel_type>
TfLiteStatus EvalMean(TfLiteContext* context, TfLiteNode* node) {
  OpContext op_context(context, node);
  OpData* data = reinterpret_cast<OpData*>(node->user_data);

  int num_axis = static_cast<int>(NumElements(op_context.axis));
  TfLiteTensor* temp_index = GetTemporary(context, node, /*index=*/0);
  TfLiteTensor* resolved_axis = GetTemporary(context, node, /*index=*/1);
  TfLiteTensor* temp_sum = GetTemporary(context, node, /*index=*/2);
  // Resize the output tensor if the output tensor is dynamic.
  if (IsDynamicTensor(op_context.output)) {
    TF_LITE_ENSURE_OK(context,
                      ResizeTempAxis(context, &op_context, resolved_axis));
    TF_LITE_ENSURE_OK(context, ResizeOutputTensor(context, &op_context));
    TF_LITE_ENSURE_OK(context, ResizeTempSum(context, &op_context, temp_sum));
  }

  if (kernel_type == kGenericOptimized) {
    // Use optimized ops if available.
    switch (op_context.input->type) {
      case kTfLiteInt8: {
        tflite::MeanParams op_params;
        op_params.axis_count = num_axis;
        ResolveAxis(GetTensorData<int>(op_context.axis), num_axis, &op_params);
        const TfLiteTensor* input = op_context.input;
        if (op_context.params->keep_dims && NumDimensions(input) == 4 &&
            op_params.axis_count == 2 &&
            ((op_params.axis[0] == 1 && op_params.axis[1] == 2) ||
             (op_params.axis[0] == 2 && op_params.axis[1] == 1))) {
          optimized_integer_ops::Mean(
              op_params, GetTensorShape(input), GetTensorData<int8_t>(input),
              input->params.zero_point, input->params.scale,
              GetTensorShape(op_context.output),
              GetTensorData<int8_t>(op_context.output),
              op_context.output->params.zero_point,
              op_context.output->params.scale,
              CpuBackendContext::GetFromContext(context));
          return kTfLiteOk;
        }
      } break;
      case kTfLiteUInt8: {
        tflite::MeanParams op_params;
        op_params.axis_count = num_axis;
        ResolveAxis(GetTensorData<int>(op_context.axis), num_axis, &op_params);
        const TfLiteTensor* input = op_context.input;
        if (op_context.params->keep_dims && NumDimensions(input) == 4 &&
            op_params.axis_count == 2 &&
            ((op_params.axis[0] == 1 && op_params.axis[1] == 2) ||
             (op_params.axis[0] == 2 && op_params.axis[1] == 1))) {
          optimized_ops::Mean(op_params, GetTensorShape(input),
                              GetTensorData<uint8_t>(input),
                              input->params.zero_point, input->params.scale,
                              GetTensorShape(op_context.output),
                              GetTensorData<uint8_t>(op_context.output),
                              op_context.output->params.zero_point,
                              op_context.output->params.scale,
                              CpuBackendContext::GetFromContext(context));
          return kTfLiteOk;
        }
      } break;
      default:
        break;
    }
  }

  // From here, it uses the reference implementations.
  // TODO(b/139102329): Clean up the function signatures to merge the variations
  // and handle the specialized cases in the combined reference implementations
  // per each op.
  switch (op_context.input->type) {
    case kTfLiteFloat32: {
      tflite::MeanParams op_params;
      op_params.axis_count = num_axis;
      ResolveAxis(GetTensorData<int>(op_context.axis), num_axis, &op_params);
      const TfLiteTensor* input = op_context.input;
      // TODO(b/139102329): Handle the below special case in the combined
      // reference method.
      // Defer to specialized implementation for 4D Mean across axes 1 & 2.
      if (op_context.params->keep_dims && NumDimensions(input) == 4 &&
          op_params.axis_count == 2 &&
          ((op_params.axis[0] == 1 && op_params.axis[1] == 2) ||
           (op_params.axis[0] == 2 && op_params.axis[1] == 1))) {
        reference_ops::Mean(op_params, GetTensorShape(input),
                            GetTensorData<float>(input),
                            GetTensorShape(op_context.output),
                            GetTensorData<float>(op_context.output));
      } else {
        TF_LITE_ENSURE(
            context,
            optimized_ops::MeanGeneral(
                GetTensorData<float>(op_context.input),
                op_context.input->dims->data, op_context.input->dims->size,
                GetTensorData<float>(op_context.output),
                op_context.output->dims->data, op_context.output->dims->size,
                GetTensorData<int>(op_context.axis), num_axis,
                op_context.params->keep_dims, GetTensorData<int>(temp_index),
                GetTensorData<int>(resolved_axis),
                GetTensorData<float>(temp_sum)));
      }
    } break;
    case kTfLiteInt32:
      TF_LITE_ENSURE(
          context,
          reference_ops::Mean(
              GetTensorData<int>(op_context.input),
              op_context.input->dims->data, op_context.input->dims->size,
              GetTensorData<int>(op_context.output),
              op_context.output->dims->data, op_context.output->dims->size,
              GetTensorData<int>(op_context.axis), num_axis,
              op_context.params->keep_dims, GetTensorData<int>(temp_index),
              GetTensorData<int>(resolved_axis),
              GetTensorData<int64_t>(temp_sum)));
      break;
    case kTfLiteInt64:
      TF_LITE_ENSURE(
          context,
          reference_ops::Mean(
              GetTensorData<int64_t>(op_context.input),
              op_context.input->dims->data, op_context.input->dims->size,
              GetTensorData<int64_t>(op_context.output),
              op_context.output->dims->data, op_context.output->dims->size,
              GetTensorData<int>(op_context.axis), num_axis,
              op_context.params->keep_dims, GetTensorData<int>(temp_index),
              GetTensorData<int>(resolved_axis),
              GetTensorData<int64_t>(temp_sum)));
      break;
    case kTfLiteInt8: {
      tflite::MeanParams op_params;
      op_params.axis_count = num_axis;
      ResolveAxis(GetTensorData<int>(op_context.axis), num_axis, &op_params);
      const TfLiteTensor* input = op_context.input;
      // TODO(b/139102329): Handle all the cases in the combined reference
      // method.
      if (op_context.params->keep_dims && NumDimensions(input) == 4 &&
          op_params.axis_count == 2 &&
          ((op_params.axis[0] == 1 && op_params.axis[1] == 2) ||
           (op_params.axis[0] == 2 && op_params.axis[1] == 1))) {
        reference_integer_ops::Mean(
            op_params, data->multiplier, data->shift, GetTensorShape(input),
            GetTensorData<int8_t>(input), op_context.input->params.zero_point,
            GetTensorShape(op_context.output),
            GetTensorData<int8_t>(op_context.output),
            op_context.output->params.zero_point);
      } else if (input->params.zero_point ==
                     op_context.output->params.zero_point &&
                 input->params.scale == op_context.output->params.scale) {
        TF_LITE_ENSURE(
            context,
            reference_ops::Mean(
                GetTensorData<int8_t>(input), input->dims->data,
                input->dims->size, GetTensorData<int8_t>(op_context.output),
                op_context.output->dims->data, op_context.output->dims->size,
                GetTensorData<int>(op_context.axis), num_axis,
                op_context.params->keep_dims, GetTensorData<int>(temp_index),
                GetTensorData<int>(resolved_axis),
                GetTensorData<int>(temp_sum)));
      } else {
        TF_LITE_ENSURE(
            context,
            reference_ops::QuantizedMeanOrSum<>(
                GetTensorData<int8_t>(input), input->params.zero_point,
                input->params.scale, input->dims->data, input->dims->size,
                GetTensorData<int8_t>(op_context.output),
                op_context.output->params.zero_point,
                op_context.output->params.scale, op_context.output->dims->data,
                op_context.output->dims->size,
                GetTensorData<int>(op_context.axis), num_axis,
                op_context.params->keep_dims, GetTensorData<int>(temp_index),
                GetTensorData<int>(resolved_axis), GetTensorData<int>(temp_sum),
                /*compute_sum=*/false));
      }
    } break;
    case kTfLiteUInt8: {
      // TODO(b/139102329): Handle all the cases in the combined reference
      // method.
      tflite::MeanParams op_params;
      op_params.axis_count = num_axis;
      ResolveAxis(GetTensorData<int>(op_context.axis), num_axis, &op_params);
      if (op_context.params->keep_dims &&
          NumDimensions(op_context.input) == 4 && op_params.axis_count == 2 &&
          ((op_params.axis[0] == 1 && op_params.axis[1] == 2) ||
           (op_params.axis[0] == 2 && op_params.axis[1] == 1))) {
        reference_ops::Mean(op_params, GetTensorShape(op_context.input),
                            GetTensorData<uint8_t>(op_context.input),
                            op_context.input->params.zero_point,
                            op_context.input->params.scale,
                            GetTensorShape(op_context.output),
                            GetTensorData<uint8_t>(op_context.output),
                            op_context.output->params.zero_point,
                            op_context.output->params.scale);
      } else if (op_context.input->params.zero_point ==
                     op_context.output->params.zero_point &&
                 op_context.input->params.scale ==
                     op_context.output->params.scale) {
        TF_LITE_ENSURE(
            context,
            reference_ops::Mean(
                GetTensorData<uint8_t>(op_context.input),
                op_context.input->dims->data, op_context.input->dims->size,
                GetTensorData<uint8_t>(op_context.output),
                op_context.output->dims->data, op_context.output->dims->size,
                GetTensorData<int>(op_context.axis), num_axis,
                op_context.params->keep_dims, GetTensorData<int>(temp_index),
                GetTensorData<int>(resolved_axis),
                GetTensorData<int>(temp_sum)));
      } else {
        TF_LITE_ENSURE(
            context,
            reference_ops::QuantizedMeanOrSum<>(
                GetTensorData<uint8_t>(op_context.input),
                op_context.input->params.zero_point,
                op_context.input->params.scale, op_context.input->dims->data,
                op_context.input->dims->size,
                GetTensorData<uint8_t>(op_context.output),
                op_context.output->params.zero_point,
                op_context.output->params.scale, op_context.output->dims->data,
                op_context.output->dims->size,
                GetTensorData<int>(op_context.axis), num_axis,
                op_context.params->keep_dims, GetTensorData<int>(temp_index),
                GetTensorData<int>(resolved_axis), GetTensorData<int>(temp_sum),
                /*compute_sum=*/false));
      }
    } break;
    default:
      return kTfLiteError;
  }
  return kTfLiteOk;
}

// The underlying logic for Reduce Sum/Prod/Max/Min/Any
template <typename T>
TfLiteStatus EvalLogic(TfLiteContext* context, TfLiteNode* node,
                       OpContext* op_context, T init_value,
                       T reducer(const T current, const T in)) {
  int64_t num_axis = NumElements(op_context->axis);
  TfLiteTensor* temp_index = GetTemporary(context, node, /*index=*/0);
  TfLiteTensor* resolved_axis = GetTemporary(context, node, /*index=*/1);
  // Resize the output tensor if the output tensor is dynamic.
  if (IsDynamicTensor(op_context->output)) {
    TF_LITE_ENSURE_OK(context,
                      ResizeTempAxis(context, op_context, resolved_axis));
    TF_LITE_ENSURE_OK(context, ResizeOutputTensor(context, op_context));
  }
  if (op_context->input->type == kTfLiteUInt8) {
    TF_LITE_ENSURE_EQ(context, op_context->input->params.scale,
                      op_context->output->params.scale);
    TF_LITE_ENSURE_EQ(context, op_context->input->params.zero_point,
                      op_context->output->params.zero_point);
  }
  TF_LITE_ENSURE(
      context,
      reference_ops::ReduceGeneric<T>(
          GetTensorData<T>(op_context->input), op_context->input->dims->data,
          op_context->input->dims->size, GetTensorData<T>(op_context->output),
          op_context->output->dims->data, op_context->output->dims->size,
          GetTensorData<int>(op_context->axis), num_axis,
          op_context->params->keep_dims, GetTensorData<int>(temp_index),
          GetTensorData<int>(resolved_axis), init_value, reducer));
  return kTfLiteOk;
}

enum ReduceType {
  kSum,
  kProd,
  kMax,
  kMin,
  kAny,
};

// Eval for determined input type and reduce type.
template <typename T>
TfLiteStatus EvalType(TfLiteContext* context, TfLiteNode* node,
                      OpContext* op_context, ReduceType reduce_type) {
  switch (reduce_type) {
    case kSum:
      return EvalLogic<T>(
          context, node, op_context, static_cast<T>(0),
          [](const T current, const T in) -> T { return in + current; });
      break;
    case kProd:
      return EvalLogic<T>(
          context, node, op_context, static_cast<T>(1),
          [](const T current, const T in) -> T { return in * current; });
      break;
    case kMax:
      return EvalLogic<T>(context, node, op_context,
                          std::numeric_limits<T>::lowest(),
                          [](const T current, const T in) -> T {
                            return (in > current) ? in : current;
                          });
      break;
    case kMin:
      return EvalLogic<T>(context, node, op_context,
                          std::numeric_limits<T>::max(),
                          [](const T current, const T in) -> T {
                            return (in < current) ? in : current;
                          });
      break;
    default:
      return kTfLiteError;
  }
}

// Template specialization for bool type
template <>
TfLiteStatus EvalType<bool>(TfLiteContext* context, TfLiteNode* node,
                            OpContext* op_context, ReduceType reduce_type) {
  switch (reduce_type) {
    case kAny:
      return EvalLogic<bool>(context, node, op_context, false,
                             [](const bool current, const bool in) -> bool {
                               return in || current;
                             });
      break;
    default:
      return kTfLiteError;
  }
}

// The entry point that handles input types and then calls template functions to
// handle ReduceType.
template <KernelType kernel_type, ReduceType reduce_type>
TfLiteStatus EvalGeneric(TfLiteContext* context, TfLiteNode* node) {
  if (kernel_type != kReference) {
    return kTfLiteOk;
  }
  OpContext op_context(context, node);
  switch (op_context.input->type) {
    case kTfLiteFloat32:
      return EvalType<float>(context, node, &op_context, reduce_type);
      break;
    case kTfLiteInt32:
      return EvalType<int>(context, node, &op_context, reduce_type);
      break;
    case kTfLiteInt64:
      return EvalType<int64_t>(context, node, &op_context, reduce_type);
      break;
    case kTfLiteUInt8:
      return EvalType<uint8_t>(context, node, &op_context, reduce_type);
      break;
    case kTfLiteInt8:
      return EvalType<int8_t>(context, node, &op_context, reduce_type);
      break;
    case kTfLiteBool:
      return EvalType<bool>(context, node, &op_context, reduce_type);
      break;
    default:
      return kTfLiteError;
  }
}

TfLiteStatus EvalSum(TfLiteContext* context, TfLiteNode* node) {
  OpContext op_context(context, node);
  ruy::profiler::ScopeLabel label("Sum");
  const auto& input = op_context.input;
  const auto& output = op_context.output;
  const bool same_scale =
      (input->params.scale == output->params.scale &&
       input->params.zero_point == output->params.zero_point);
  const bool eight_bit_quantized =
      input->type == kTfLiteUInt8 || input->type == kTfLiteInt8;
  const bool need_rescale = (eight_bit_quantized && !same_scale);
  if (need_rescale) {
    // Rescaling 8bit reduce sum.
    int num_axis = static_cast<int>(NumElements(op_context.axis));
    TfLiteTensor* temp_index = GetTemporary(context, node, /*index=*/0);
    TfLiteTensor* resolved_axis = GetTemporary(context, node, /*index=*/1);
    TfLiteTensor* temp_sum = GetTemporary(context, node, /*index=*/2);
    // Resize the output tensor if the output tensor is dynamic.
    if (IsDynamicTensor(op_context.output)) {
      TF_LITE_ENSURE_OK(context,
                        ResizeTempAxis(context, &op_context, resolved_axis));
      TF_LITE_ENSURE_OK(context, ResizeOutputTensor(context, &op_context));
      TF_LITE_ENSURE_OK(context, ResizeTempSum(context, &op_context, temp_sum));
    }
    if (input->type == kTfLiteUInt8) {
      TF_LITE_ENSURE(
          context,
          reference_ops::QuantizedMeanOrSum<>(
              GetTensorData<uint8_t>(op_context.input),
              op_context.input->params.zero_point,
              op_context.input->params.scale, op_context.input->dims->data,
              op_context.input->dims->size,
              GetTensorData<uint8_t>(op_context.output),
              op_context.output->params.zero_point,
              op_context.output->params.scale, op_context.output->dims->data,
              op_context.output->dims->size,
              GetTensorData<int>(op_context.axis), num_axis,
              op_context.params->keep_dims, GetTensorData<int>(temp_index),
              GetTensorData<int>(resolved_axis), GetTensorData<int32>(temp_sum),
              /*compute_sum=*/true));
    }
    if (input->type == kTfLiteInt8) {
      TF_LITE_ENSURE(
          context,
          reference_ops::QuantizedMeanOrSum<>(
              GetTensorData<int8_t>(op_context.input),
              op_context.input->params.zero_point,
              op_context.input->params.scale, op_context.input->dims->data,
              op_context.input->dims->size,
              GetTensorData<int8_t>(op_context.output),
              op_context.output->params.zero_point,
              op_context.output->params.scale, op_context.output->dims->data,
              op_context.output->dims->size,
              GetTensorData<int>(op_context.axis), num_axis,
              op_context.params->keep_dims, GetTensorData<int>(temp_index),
              GetTensorData<int>(resolved_axis), GetTensorData<int32>(temp_sum),
              /*compute_sum=*/true));
    }
  } else {
    return EvalGeneric<kReference, kSum>(context, node);
  }

  return kTfLiteOk;
}
}  // namespace reduce

TfLiteRegistration* Register_MEAN_OPT() {
  static TfLiteRegistration r = {reduce::Init, reduce::Free,
                                 reduce::PrepareMeanOrSum,
                                 reduce::EvalMean<reduce::kGenericOptimized>};
  return &r;
}

TfLiteRegistration* Register_MEAN_REF() {
  static TfLiteRegistration r = {reduce::Init, reduce::Free,
                                 reduce::PrepareMeanOrSum,
                                 reduce::EvalMean<reduce::kReference>};
  return &r;
}

TfLiteRegistration* Register_SUM_REF() {
  static TfLiteRegistration r = {reduce::Init, reduce::Free,
                                 reduce::PrepareMeanOrSum, reduce::EvalSum};
  return &r;
}

TfLiteRegistration* Register_REDUCE_PROD_REF() {
  static TfLiteRegistration r = {
      reduce::Init, reduce::Free, reduce::PrepareSimple,
      reduce::EvalGeneric<reduce::kReference, reduce::kProd>};
  return &r;
}

TfLiteRegistration* Register_REDUCE_MAX_REF() {
  static TfLiteRegistration r = {
      reduce::Init, reduce::Free, reduce::PrepareSimple,
      reduce::EvalGeneric<reduce::kReference, reduce::kMax>};
  return &r;
}

TfLiteRegistration* Register_REDUCE_MIN_REF() {
  static TfLiteRegistration r = {
      reduce::Init, reduce::Free, reduce::PrepareSimple,
      reduce::EvalGeneric<reduce::kReference, reduce::kMin>};
  return &r;
}

TfLiteRegistration* Register_REDUCE_ANY_REF() {
  static TfLiteRegistration r = {
      reduce::Init, reduce::Free, reduce::PrepareAny,
      reduce::EvalGeneric<reduce::kReference, reduce::kAny>};
  return &r;
}

TfLiteRegistration* Register_MEAN() {
#ifdef USE_NEON
  return Register_MEAN_OPT();
#else
  return Register_MEAN_REF();
#endif
}

TfLiteRegistration* Register_SUM() { return Register_SUM_REF(); }
TfLiteRegistration* Register_REDUCE_PROD() {
  return Register_REDUCE_PROD_REF();
}
TfLiteRegistration* Register_REDUCE_MAX() { return Register_REDUCE_MAX_REF(); }
TfLiteRegistration* Register_REDUCE_MIN() { return Register_REDUCE_MIN_REF(); }
TfLiteRegistration* Register_REDUCE_ANY() { return Register_REDUCE_ANY_REF(); }

}  // namespace builtin
}  // namespace ops
}  // namespace tflite
