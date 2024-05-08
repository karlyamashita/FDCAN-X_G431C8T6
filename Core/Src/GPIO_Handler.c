/*
 * GPIO_Handler.c
 *
 *  Created on: May 7, 2024
 *      Author: karl.yamashita
 */

#include "main.h"



void LED_GreenBlink(void)
{
	HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
}

void LED_BlueBlink(void)
{
	HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
}

