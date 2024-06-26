/*
 * handler.h
 *
 *  Created on: Apr 28, 2024
 *      Author: BaoThuan
 */

#ifndef _INCLUDE_HANDLER_H_
#define _INCLUDE_HANDLER_H_

#include "stm32f1xx_hal.h"
#include <L7d_595.h>

typedef enum
{
	MODE_1 = 1,		// music
	MODE_2			// time base
}MODE_STATUS;

typedef enum
{
	HANDLER_OKE = 1,		// music
	HANDLER_FAIL			// time base
}HANDLER_STATE;

extern uint8_t count_mode2;
extern uint16_t value_ADC1[2];
extern uint16_t thre_MIC;
extern MODE_STATUS mode_status;

void init_handler(ADC_HandleTypeDef* hadc, TIM_HandleTypeDef* htim);
//void ON_ALL();
//void OFF_ALL();
HANDLER_STATE Mode1_handl();
HANDLER_STATE Mode2_handl();
HANDLER_STATE Handler_Led();

#endif /* _INCLUDE_HANDLER_H_ */
