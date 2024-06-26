/*
 * lL7d_595.c
 *
 *  Created on: Apr 28, 2024
 *      Author: BaoThuan
 */
#include <L7d_595.h>

/*74HC595 Port*/
static GPIO_TypeDef *					IC74HC595_ST_Port;
static GPIO_TypeDef * 					IC74hc595_DS_Port;
static GPIO_TypeDef * 					IC74HC595_Shift_Port;
/*74HC595 Pin*/
static uint16_t 						IC74hc595_Shift_Pin;
static uint16_t							IC74hc595_DS_Pin;
static uint16_t							IC74HC595_ST_Pin;

#if _7SEG_ANODE == 1
uint16_t L7_Anode[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F,  0x6F };// ma hien thi led 7 doan AM CHUNG
#elif _7SEG_KATHODE == 1
uint16_t L7_Kathode[10] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99,0x92, 0x82, 0xF8, 0x80,  0x90 };//MA LED 7 DOAN DUONG CHUNG
#endif
/**
  * @brief
  * @param
  * @retval
  */
void L7D_74HC595_Init(	GPIO_TypeDef * DS_Port, GPIO_TypeDef * Shift_Port, GPIO_TypeDef * ST_Port, 			\
						uint16_t DS_Pin, uint16_t SH_Pin, uint16_t ST_Pin)									\
{
	IC74HC595_ST_Port		=	ST_Port;
	IC74hc595_DS_Port		= 	DS_Port;
	IC74HC595_Shift_Port	=	Shift_Port;
	IC74HC595_ST_Pin		=	ST_Pin;
	IC74hc595_Shift_Pin		=	SH_Pin;
	IC74hc595_DS_Pin		=	DS_Pin;
}



/**
  * @brief
  * @param
  * @retval
  */
void L7D_74HC595_Set_Reset(uint16_t  tt1, uint16_t  tt2)
{
	uint16_t	tam1 	= 	tt1;
	uint16_t	tam2 	= 	tt2;
	uint8_t		i 		= 	0;
	uint8_t		j 		= 	0;
	for(i = 0; i < 8; i++)
	{
		if(tam1 & (0x80 >> i))
		{
			HAL_GPIO_WritePin(IC74hc595_DS_Port, IC74hc595_DS_Pin, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(IC74hc595_DS_Port, IC74hc595_DS_Pin, GPIO_PIN_RESET);
		}
		HAL_GPIO_WritePin(IC74HC595_Shift_Port, IC74hc595_Shift_Pin ,GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(IC74HC595_Shift_Port, IC74hc595_Shift_Pin, GPIO_PIN_RESET);
		HAL_Delay(1);
	}

	for(j = 0; j < 8; j++)
	{
		if(tam2 & (0x80 >> j))
		{
			HAL_GPIO_WritePin(IC74hc595_DS_Port, IC74hc595_DS_Pin, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(IC74hc595_DS_Port, IC74hc595_DS_Pin, GPIO_PIN_RESET);
		}
		HAL_GPIO_WritePin(IC74HC595_Shift_Port, IC74hc595_Shift_Pin ,GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(IC74HC595_Shift_Port, IC74hc595_Shift_Pin, GPIO_PIN_RESET);
		HAL_Delay(1);
	}

	HAL_GPIO_WritePin(IC74HC595_ST_Port, IC74HC595_ST_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(IC74HC595_ST_Port, IC74HC595_ST_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
}
