To configure Timer2 for input capture using the Low Speed External (LSE) clock on an STM32F446RE microcontroller with STM32CubeMX, follow these detailed step-by-step instructions. The goal is to set up Timer2 to capture its counter value based on the LSE clock signal, which operates at 32.768 kHz. Since the LSE is an internal clock source and not directly available as an input capture trigger, we’ll output it via the Microcontroller Clock Output (MCO) on a pin and connect it externally to Timer2’s input capture channel.

Step-by-Step Configuration in STM32CubeMX
Launch STM32CubeMX and Select the Microcontroller
Open STM32CubeMX.
Start a new project by selecting the STM32F446RE microcontroller from the device selector.
Configure the Clock
Navigate to the Clock Configuration tab.
Enable the Low Speed External (LSE) clock:
Under "LSE," select Crystal/Ceramic Resonator (assuming a 32.768 kHz crystal is connected to the OSC32_IN and OSC32_OUT pins).
This activates the LSE clock, which will be used as the signal source.
Set Up the MCO to Output LSE
Go to the Pinout & Configuration tab.
Under System Core, select RCC (Reset and Clock Control).
In the RCC configuration:
Find the MCO (Microcontroller Clock Output) setting.
Set MCO to LSE. This configures pin PA8 to output the LSE clock signal (32.768 kHz).
Configure Timer2 for Input Capture
In the Pinout & Configuration tab, go to Timers and select TIM2.
Enable Channel 1 for input capture:
Set Channel 1 to Input Capture Direct Mode.
This automatically assigns PA0 as TIM2_CH1, the input pin for Timer2’s Channel 1.
Adjust TIM2 Parameters
Still under TIM2 in the Configuration tab:
Prescaler: Set to 0 (no division, for maximum resolution of the timer clock).
Counter Mode: Set to Up (timer counts upward).
Period: Set to 65535 (maximum value for a 16-bit timer, allowing the widest range for captures).
Under Channel 1 settings:
Polarity: Set to Rising Edge (captures the timer value on the rising edge of the input signal).
Input Filter: Set to 0 (no filtering, or adjust based on noise requirements).
Note: Timer2’s clock source is derived from the APB1 clock (typically 84 MHz in high-performance configurations), not the LSE directly. The LSE will be the input signal to capture.
Enable Timer2 Interrupt
In the NVIC Settings tab (Nested Vectored Interrupt Controller):
Check the box for TIM2 global interrupt to enable interrupt handling for input capture events.
This allows the microcontroller to trigger an interrupt each time a capture occurs, so you can process the captured values.
Generate the Project Code
Click the Generate Code button (gear icon) in STM32CubeMX.
Choose your preferred IDE (e.g., STM32CubeIDE, Keil, or IAR) and generate the project files.
This creates the initialization code based on your configuration.
Hardware Connection
In your physical hardware setup:
Connect pin PA8 (MCO, outputting the LSE clock) to pin PA0 (TIM2_CH1) externally using a jumper wire or PCB trace.
This routes the 32.768 kHz LSE signal to Timer2’s input capture channel.