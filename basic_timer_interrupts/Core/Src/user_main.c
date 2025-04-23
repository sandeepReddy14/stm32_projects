/*
 * user_main.c
 *
 *  Created on: Apr 23, 2025
 *      Author: sandeep
 */

#include <string.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "user_main.h"
#include "user_msp.h"
#include "stm32f4xx_hal_tim.h"
#include "user_msp.h"
#include "stm32f446xx.h"

#define UART_DATA_MAX_LENGTH     128

UART_HandleTypeDef huart2;

uint8_t uart_data_buffer[UART_DATA_MAX_LENGTH+1];


/* Timer 6 variables */
TIM_HandleTypeDef tim6_handle;

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}



/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

static void switch_to_hsi(void)
{
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
	uint8_t flash_latency = FLASH_LATENCY_0;

	/* Switch to HSI to safely reconfigure PLL */

	/* Oscillator initialization */
	memset(&osc_init,0,sizeof(osc_init));

	/* Clock Initialization */
	memset(&clk_init,0,sizeof(clk_init));

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	osc_init.PLL.PLLState = RCC_PLL_NONE;

	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clk_init.APB1CLKDivider = RCC_HCLK_DIV1;
	clk_init.APB2CLKDivider = RCC_HCLK_DIV1;

	/* Oscillator config init */
	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
	{
		Error_Handler();
	}

	/* Clock Config */
	if(HAL_RCC_ClockConfig(&clk_init, flash_latency) != HAL_OK)
	{
		Error_Handler();
	}

}

/* clock_freq in Mhz */
static void SystemClockConfigPllHSE(uint8_t clock_freq)
{

	switch_to_hsi();

	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
	uint8_t flash_latency = FLASH_LATENCY_0;

	/* Oscillator initialization */
	memset(&osc_init,0,sizeof(osc_init));

	/* Clock Initialization */
	memset(&clk_init,0,sizeof(clk_init));

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_BYPASS;

	/* PLL config */
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;

	switch(clock_freq)
	{
		case SYS_CLOCK_FREQ_50_MHZ:
		{
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 100;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			flash_latency = FLASH_LATENCY_1;
		}
		break;
		case SYS_CLOCK_FREQ_84_MHZ:
		{
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 168;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			flash_latency = FLASH_LATENCY_2;
		}
		break;
		case SYS_CLOCK_FREQ_120_MHZ:
		{
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 240;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			flash_latency = FLASH_LATENCY_3;
		}
		break;
		case SYS_CLOCK_FREQ_180_MHZ:
		{
			/* Enable clock for the power controller */
			__HAL_RCC_PWR_CLK_ENABLE();
			/* Set regulator voltage scale as 1*/
			__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
			/* Turn on the power drive mode of the voltage regulator */
			__HAL_PWR_OVERDRIVE_ENABLE();


			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 360;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			flash_latency = FLASH_LATENCY_5;

		}
		break;
		default:
		{
			while(1);
		}
		break;
	}

	/* Oscillator config init */
	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
	{
		Error_Handler();
	}

	/* Clock Config */
	if(HAL_RCC_ClockConfig(&clk_init, flash_latency) != HAL_OK)
	{
		Error_Handler();
	}

	/* disable internal clock */
	__HAL_RCC_HSI_DISABLE();


	/* SYSTICK Configuration */
	if(HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}


static void TIMER6_Init(void)
{
	tim6_handle.Instance = TIM6;

	tim6_handle.Init.Prescaler = 99;
	tim6_handle.Init.Period = ((HSI_CLOCK_FREQ_KHZ * 100) / (tim6_handle.Init.Prescaler)) - 1;


	if(HAL_TIM_Base_Init(&tim6_handle) != HAL_OK)
	{
		Error_Handler();
	}
}

static void GPIO_Init(void)
{
	__HAL_RCC_GPIO_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOA, &ledgpio);
}

int main(void)
{
	HAL_Init();

	switch_to_hsi();

	MX_USART2_UART_Init();

	GPIO_Init();

	TIMER6_Init();

	/* Start Timer */
	HAL_TIM_Base_Start(&tim6_handle);

	while(1)
	{
		while( !(TIM6->SR & TIM_SR_UIF))
		{
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			TIM6->SR = 0;
		}

	}







	while(1);

	return 0;
}
