/*
 * user_msp.h
 *
 *  Created on: Apr 23, 2025
 *      Author: sandeep
 */

#ifndef INC_USER_MSP_H_
#define INC_USER_MSP_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_tim.h"

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base);



#endif /* INC_USER_MSP_H_ */
