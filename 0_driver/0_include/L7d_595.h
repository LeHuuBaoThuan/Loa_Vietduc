/*
 * L7d_595.h
 *
 *  Created on: Apr 28, 2024
 *      Author: BaoThuan
 */

#ifndef _INCLUDE_L7D_595_H_
#define _INCLUDE_L7D_595_H_

#include "stm32f1xx_hal.h"

#define _7SEG_KATHODE 	1
#define _7SEG_ANODE 	0

#if _7SEG_ANODE == 1
extern uint16_t L7_Anode[10];
#elif _7SEG_KATHODE == 1
extern uint16_t L7_Kathode[10];
#endif

void L7D_74HC595_Init(	GPIO_TypeDef * DS_Port, GPIO_TypeDef * Shift_Port, GPIO_TypeDef * ST_Port, 			\
						uint16_t DS_Pin, uint16_t SH_Pin, uint16_t ST_Pin);									\

void L7D_74HC595_Set_Reset(uint16_t  tt1, uint16_t  tt2);

#endif /* _INCLUDE_L7D_595_H_ */
