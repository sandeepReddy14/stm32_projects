### PLL Dynamic Reconfiguration Project Using HSE as PLL input
- **Description**: Configures the PLL on STM32F446RE to max frequencies SYSCLK as 180MHz, HCLK 180MHz, PCLK1 45MHz and PCLK2 90MHz with UART logging.
- **Safety Mechanism**: Switches to HSE (16 MHz) before reconfiguring PLL to maintain system stability during clock changes.