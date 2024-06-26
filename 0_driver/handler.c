/*
 * handler.c
 *
 *  Created on: Apr 28, 2024
 *      Author: BaoThuan
 */
#include <handler.h>

uint16_t value_ADC1[2] = {0};	// Phan tu 0: tuong ung mic doc duoc
								// Phan tu 1: tuong ung che do nhap nhay may giay mode 2
uint16_t thre_MIC = 1400;

uint8_t count_mode2 = 1;

MODE_STATUS mode_status = MODE_1;

static ADC_HandleTypeDef* hadc1_fnc;
static TIM_HandleTypeDef* htim2_fnc;


/**
  * @brief 		Khoi tao
  * @param
  * @retval
  */
void init_handler(ADC_HandleTypeDef* hadc, TIM_HandleTypeDef* htim)
{
	htim2_fnc = htim;
	hadc1_fnc = hadc;
}

/**
  * @brief 		BAT Den 220V 100W
  * @param
  * @retval
  */
static void OFF_ALL(void)
{
	GPIOB->ODR &= ~(GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);// reset
}


/**
  * @brief		TAT Den 220V 100W
  * @param
  * @retval
  */
static void ON_ALL(void)
{
	GPIOB->ODR |= (GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);// set
}

/**
  * @brief		Ham xu lu MODE1 - Doc ADC0 - Bat tat DEN 220V 100W
  * @param
  * @retval
  */
HANDLER_STATE Mode1_handl(void)
{
//	HAL_TIM_Base_Stop_IT(htim2_fnc);
	/*SO SANH GIA TRI VA BLINK*/
	if (value_ADC1[0] > thre_MIC)
	{
		ON_ALL();
	}
	else
	{
		OFF_ALL();
	}
	return HANDLER_OKE;
}


/**
  * @brief		Ham xu lu MODE2 - Doc ADC1 => delay bao nhieu giay timer - Bat tat DEN 220V 100W
  * @param
  * @retval
  */
HANDLER_STATE Mode2_handl(void)
{
//	HAL_TIM_Base_Start_IT(htim2_fnc);
	/*SO SANH GIA TRI VA THAY DOI GIA TRI DELAY*/
	if(value_ADC1[1] < 819)
		count_mode2 = 1;
	else if(value_ADC1[1] < 819 * 2)
		count_mode2 = 2;
	else if(value_ADC1[1] < 819 * 3)
		count_mode2 = 3;
	else if(value_ADC1[1] < 819 * 4)
		count_mode2 = 4;
	else if(value_ADC1[1] <= 819 * 5)
		count_mode2 = 5;
	else
		count_mode2 = 1;
	return HANDLER_OKE;
}


/**
  * @brief		Ham xu ly chon che do MODE1 | MODE2
  * @param
  * @retval
  */
HANDLER_STATE Handler_Led(void)
{
	/*CHE DO 1*/
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == GPIO_PIN_RESET)
	{
		mode_status = MODE_1;
		if(Mode1_handl() != HANDLER_OKE)
			return HANDLER_FAIL;
	}
	/*CHE DO 2*/
	else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == GPIO_PIN_SET)
	{
		mode_status = MODE_2;
		if(Mode2_handl() != HANDLER_OKE)
			return HANDLER_FAIL;
	}
	L7D_74HC595_Set_Reset(L7_Kathode[count_mode2], L7_Kathode[mode_status]);
	return HANDLER_OKE;
}
