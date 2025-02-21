if(NOT MIDDLEWARE_FREERTOS-KERNEL_K32L2B31A_INCLUDED)
    
    set(MIDDLEWARE_FREERTOS-KERNEL_K32L2B31A_INCLUDED true CACHE BOOL "middleware_freertos-kernel component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/freertos_kernel/event_groups.c
        ${CMAKE_CURRENT_LIST_DIR}/freertos_kernel/croutine.c
        ${CMAKE_CURRENT_LIST_DIR}/freertos_kernel/list.c
        ${CMAKE_CURRENT_LIST_DIR}/freertos_kernel/portable/GCC/ARM_CM0/port.c
        ${CMAKE_CURRENT_LIST_DIR}/freertos_kernel/queue.c
        ${CMAKE_CURRENT_LIST_DIR}/freertos_kernel/stream_buffer.c
        ${CMAKE_CURRENT_LIST_DIR}/freertos_kernel/tasks.c
        ${CMAKE_CURRENT_LIST_DIR}/freertos_kernel/timers.c
    )


    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/freertos_kernel/include
        ${CMAKE_CURRENT_LIST_DIR}/freertos_kernel/portable/GCC/ARM_CM0
    )


    include(middleware_freertos-kernel_extension_K32L2B31A)

endif()
