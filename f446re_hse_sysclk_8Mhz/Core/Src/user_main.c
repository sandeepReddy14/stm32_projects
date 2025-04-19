/*
 * user_main.c
 *
 *  Created on: Apr 20, 2025
 *      Author: sandeep
 */

#include <string.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"

#define UART_DATA_MAX_LENGTH     128

UART_HandleTypeDef huart2;

uint8_t uart_data_buffer[UART_DATA_MAX_LENGTH+1];


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

int main(void)
{

	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;


	HAL_Init();


	/* Oscillator initialization */
	memset(&osc_init,0,sizeof(osc_init));
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_BYPASS;

	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
	{
		Error_Handler();
	}

	/* Clock Initialization */
	memset(&clk_init,0,sizeof(clk_init));


	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2;
	clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
	clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

	if(HAL_RCC_ClockConfig(&clk_init, FLASH_LATENCY_0) != HAL_OK)
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

	MX_USART2_UART_Init();

	/* print details of each configuration every 3 seconds */
	while(1)
	{
		/* SYSCLK */
		memset(&uart_data_buffer,0,sizeof(uart_data_buffer));
		sprintf(uart_data_buffer,"SYSCLK : %ldHz\r\n",HAL_RCC_GetSysClockFreq());
		HAL_UART_Transmit(&huart2,uart_data_buffer,strlen(uart_data_buffer),HAL_MAX_DELAY);

		/* HCLK */
		memset(&uart_data_buffer,0,sizeof(uart_data_buffer));
		sprintf(uart_data_buffer,"HCLK   : %ldHz\r\n",HAL_RCC_GetHCLKFreq());
		HAL_UART_Transmit(&huart2,uart_data_buffer,strlen(uart_data_buffer),HAL_MAX_DELAY);

		/* PCLK1 */
		memset(&uart_data_buffer,0,sizeof(uart_data_buffer));
		sprintf(uart_data_buffer,"PCLK1  : %ldHz\r\n",HAL_RCC_GetPCLK1Freq());
		HAL_UART_Transmit(&huart2,uart_data_buffer,strlen(uart_data_buffer),HAL_MAX_DELAY);

		/* PCLK2 */
		memset(&uart_data_buffer,0,sizeof(uart_data_buffer));
		sprintf(uart_data_buffer,"PCLK2  : %ldHz\r\n",HAL_RCC_GetPCLK2Freq());
		HAL_UART_Transmit(&huart2,uart_data_buffer,strlen(uart_data_buffer),HAL_MAX_DELAY);

		HAL_Delay(3000);

	}




	while(1);

	return 0;
}
