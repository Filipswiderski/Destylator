/*
 * heater.c
 *
 *  Created on: Dec 20, 2020
 *      Author: hp
 */

#include "heater.h"
#include "stm32g0xx_hal.h"
#include "main.h"


void heaterEnable(void){
	HAL_GPIO_WritePin(HEATER_GPIO_Port, HEATER_Pin, GPIO_PIN_SET);
}

void heaterDisable(void){
	HAL_GPIO_WritePin(HEATER_GPIO_Port, HEATER_Pin, GPIO_PIN_RESET);
}
