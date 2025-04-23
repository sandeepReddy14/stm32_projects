/*
 * user_msp.c
 *
 *  Created on: Apr 23, 2025
 *      Author: sandeep
 */
#include "user_msp.h"
#include "stm32f4xx_hal_tim.h"

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

	/* Enable clock for TIM6 peripheral */
	__HAL_RCC_TIM6_CLK_ENABLE();

	/* Enable IRQ for TIM6 */
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	/* configure Priority */
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 15, 0);

}
