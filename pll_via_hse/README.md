### PLL Dynamic Reconfiguration Project Using HSE as PLL input
- **Description**: Dynamically reconfigures the PLL on STM32F446RE to switch HCLK frequencies ( 50MHz, 84 MHz, 120 MHz) with UART logging.
- **Safety Mechanism**: Switches to HSE (16 MHz) before reconfiguring PLL to maintain system stability during clock changes.