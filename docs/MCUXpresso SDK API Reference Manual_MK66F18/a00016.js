var a00016 =
[
    [ "dac_config_t", "a00016.html#a00304", [
      [ "referenceVoltageSource", "a00016.html#a4a02511eeb7a57b6f959dd87646db467", null ],
      [ "enableLowPowerMode", "a00016.html#a7bc0e37a90b0fe5c7c8602a72a5a585f", null ]
    ] ],
    [ "dac_buffer_config_t", "a00016.html#a00303", [
      [ "triggerMode", "a00016.html#abb44460b37a3d7e80983d9e6745fb00a", null ],
      [ "watermark", "a00016.html#a9eefabfa144f5c4728af3b2656462bf1", null ],
      [ "workMode", "a00016.html#a646a46fe3ece9060591d66d6bc14b834", null ],
      [ "upperLimit", "a00016.html#a6d2cae6b10a2039b3bb9c1552d750040", null ]
    ] ],
    [ "FSL_DAC_DRIVER_VERSION", "a00016.html#ga530714225167c7f0e4526943afc474ad", null ],
    [ "_dac_buffer_status_flags", "a00016.html#ga52548bc3e8fd7b2df05186d1b32ea648", [
      [ "kDAC_BufferWatermarkFlag", "a00016.html#gga52548bc3e8fd7b2df05186d1b32ea648a85fcecf62140e90d2e56adfcb5d17bd4", null ],
      [ "kDAC_BufferReadPointerTopPositionFlag", "a00016.html#gga52548bc3e8fd7b2df05186d1b32ea648aacf10971c5e7d4696f9b8f9764f9c82e", null ],
      [ "kDAC_BufferReadPointerBottomPositionFlag", "a00016.html#gga52548bc3e8fd7b2df05186d1b32ea648ace46a42e8650cfc8f3f431855e91b503", null ]
    ] ],
    [ "_dac_buffer_interrupt_enable", "a00016.html#ga556c5ba2343e258c26f1b1af05a81e1a", [
      [ "kDAC_BufferWatermarkInterruptEnable", "a00016.html#gga556c5ba2343e258c26f1b1af05a81e1aaf2c874888760a3b2a07ce954544dc76b", null ],
      [ "kDAC_BufferReadPointerTopInterruptEnable", "a00016.html#gga556c5ba2343e258c26f1b1af05a81e1aaf4cbf619f6230ab146b141f4b9d0771b", null ],
      [ "kDAC_BufferReadPointerBottomInterruptEnable", "a00016.html#gga556c5ba2343e258c26f1b1af05a81e1aa73a1fd0e6856d29fdb9863a7bd0e9cea", null ]
    ] ],
    [ "dac_reference_voltage_source_t", "a00016.html#ga05db8184073a676ea7762e08ba0e53ac", [
      [ "kDAC_ReferenceVoltageSourceVref1", "a00016.html#gga05db8184073a676ea7762e08ba0e53acad4013ec0dffa1ce8d7bca994c8ed4e28", null ],
      [ "kDAC_ReferenceVoltageSourceVref2", "a00016.html#gga05db8184073a676ea7762e08ba0e53acaab0852243da81673a102a1a86ffafa59", null ]
    ] ],
    [ "dac_buffer_trigger_mode_t", "a00016.html#gae4fa7fe6dff788f277d9ce00197bb78c", [
      [ "kDAC_BufferTriggerByHardwareMode", "a00016.html#ggae4fa7fe6dff788f277d9ce00197bb78cafbc03d98f1b69257187778ab4a9a5cfe", null ],
      [ "kDAC_BufferTriggerBySoftwareMode", "a00016.html#ggae4fa7fe6dff788f277d9ce00197bb78ca4f11acf8c8b116275fee60a42f907cdd", null ]
    ] ],
    [ "dac_buffer_watermark_t", "a00016.html#gaa4e9ebe1e5a2a7a58a0f15c8ed331130", [
      [ "kDAC_BufferWatermark1Word", "a00016.html#ggaa4e9ebe1e5a2a7a58a0f15c8ed331130af503d5348333ac977d94c9e619fd85e7", null ],
      [ "kDAC_BufferWatermark2Word", "a00016.html#ggaa4e9ebe1e5a2a7a58a0f15c8ed331130a160829eee4e44b94a709ba7ea059c144", null ],
      [ "kDAC_BufferWatermark3Word", "a00016.html#ggaa4e9ebe1e5a2a7a58a0f15c8ed331130a9354deb0a46eef62c31089f35886c267", null ],
      [ "kDAC_BufferWatermark4Word", "a00016.html#ggaa4e9ebe1e5a2a7a58a0f15c8ed331130a61f304c9830aec2fa202aa375bdf5bf4", null ]
    ] ],
    [ "dac_buffer_work_mode_t", "a00016.html#gaa6dee8fad888f630dcef291d7474f5e8", [
      [ "kDAC_BufferWorkAsNormalMode", "a00016.html#ggaa6dee8fad888f630dcef291d7474f5e8aebbceb6d7cecef81259c2bfdbde6dd88", null ],
      [ "kDAC_BufferWorkAsSwingMode", "a00016.html#ggaa6dee8fad888f630dcef291d7474f5e8a37ec9cac0229fbd27e2813e897085886", null ],
      [ "kDAC_BufferWorkAsOneTimeScanMode", "a00016.html#ggaa6dee8fad888f630dcef291d7474f5e8adc07bbd0e997b6a33c10c721851f6f7c", null ]
    ] ],
    [ "DAC_Init", "a00016.html#ga0331d8c8f699fac12c93a7796d961923", null ],
    [ "DAC_Deinit", "a00016.html#gab9cec79763041b1df321a5839982feba", null ],
    [ "DAC_GetDefaultConfig", "a00016.html#ga18bbc1eedecdc090c14578740271db0e", null ],
    [ "DAC_Enable", "a00016.html#ga8744607939abfe64891c8aaa05a97a29", null ],
    [ "DAC_EnableBuffer", "a00016.html#gacece0d7102d1a94eaef40f4704d847bf", null ],
    [ "DAC_SetBufferConfig", "a00016.html#gab36195fbf4d2e0bb0771fc6c102c7688", null ],
    [ "DAC_GetDefaultBufferConfig", "a00016.html#gadfcaccffddd058eebaa8135fe92e74cb", null ],
    [ "DAC_EnableBufferDMA", "a00016.html#gac5a97c9c7af23a63a9c00b0830726f41", null ],
    [ "DAC_SetBufferValue", "a00016.html#ga14a1c0caecddc89b462e9387392956df", null ],
    [ "DAC_DoSoftwareTriggerBuffer", "a00016.html#ga40dfcfcef8ee39068af9197746a18023", null ],
    [ "DAC_GetBufferReadPointer", "a00016.html#ga977f3c916c8fa06769f752cc66005bd4", null ],
    [ "DAC_SetBufferReadPointer", "a00016.html#gaa5716743c53f64cc4064f27d92c91e2a", null ],
    [ "DAC_EnableBufferInterrupts", "a00016.html#gae81f8ddb0f53db26bc23d19eef80fd3c", null ],
    [ "DAC_DisableBufferInterrupts", "a00016.html#ga026dd197d500e58f96bbbcf5105b9d72", null ],
    [ "DAC_GetBufferStatusFlags", "a00016.html#ga4418075ad09bc816b186dc9bc4d64f7c", null ],
    [ "DAC_ClearBufferStatusFlags", "a00016.html#ga5df52b8f725cccd40c6dbd2ec542dfbe", null ]
];