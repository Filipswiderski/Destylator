/*
 * display7seg.c
 *
 *  Created on: Dec 20, 2020
 *      Author: hp
 */

#include "display7seg.h"
#include "stm32g0xx_hal.h"
#include "main.h"
#include <stdbool.h>

#define DISPLAY_7_SEG_DIGITS (2)
#define DISPLAY_7_SEG_SEGMENTS (7)
#define DISPLAY_7_SEG_DECIMAL (10)


static void setA(bool state);
static void setB(bool state);
static void setC(bool state);
static void setD(bool state);
static void setE(bool state);
static void setF(bool state);
static void setG(bool state);

static void printDigit(uint8_t);

extern TIM_HandleTypeDef htim17;

static volatile uint32_t digit = 0;
static volatile uint8_t value[DISPLAY_7_SEG_DIGITS];
static volatile bool enableDisplay;

static const bool segmentValues[DISPLAY_7_SEG_DECIMAL][DISPLAY_7_SEG_SEGMENTS] = {
	{true, true, true, true, true, true, false},		// 0
	{false, true, true, false, false, false, false},	// 1
	{true, true, false, true, true, false, true},		// 2
	{true, true, true, true, false, false, true},		// 3
	{false, true, true, false, false, true, true},		// 4
	{true, false, true, true, false, true, true},		// 5
	{true, false, true, true, true, true, true},		// 6
	{true, true, true, false, false, false, false},		// 7
	{true, true, true, true, true, true, true},			// 8
	{true, true, true, true, false, true, true}			// 9
};

void display7segInit(void){
	HAL_TIM_Base_Start_IT(&htim17);

	enableDisplay = true;
}

void display7Enable(bool enable){
	enableDisplay = enable;
}

void display7segWrite(uint8_t num) {
	if(num > 99){
		num = 99;
	}

	uint8_t decimal = num / 10;
	uint8_t single = num % 10;

	value[0] = decimal;
	value[1] = single;
}

void display7segInterruptHandler(void){
	printDigit(value[digit]);

	if(enableDisplay) {
		if(digit == 0){
			HAL_GPIO_WritePin(DISPLAY_1_GPIO_Port, DISPLAY_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DISPLAY_2_GPIO_Port, DISPLAY_2_Pin, GPIO_PIN_SET);
		}
		else if(digit == 1){
			HAL_GPIO_WritePin(DISPLAY_1_GPIO_Port, DISPLAY_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DISPLAY_2_GPIO_Port, DISPLAY_2_Pin, GPIO_PIN_RESET);
		}
	}
	else {
		HAL_GPIO_WritePin(DISPLAY_1_GPIO_Port, DISPLAY_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DISPLAY_2_GPIO_Port, DISPLAY_2_Pin, GPIO_PIN_SET);
	}

	digit++;

	if(digit >= DISPLAY_7_SEG_DIGITS){
		digit = 0;
	}
}

static void setA(bool state){
	HAL_GPIO_WritePin(DISPLAY_A_GPIO_Port, DISPLAY_A_Pin, state ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

static void setB(bool state){
	HAL_GPIO_WritePin(DISPLAY_B_GPIO_Port, DISPLAY_B_Pin, state ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

static void setC(bool state){
	HAL_GPIO_WritePin(DISPLAY_C_GPIO_Port, DISPLAY_C_Pin, state ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

static void setD(bool state){
	HAL_GPIO_WritePin(DISPLAY_D_GPIO_Port, DISPLAY_D_Pin, state ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

static void setE(bool state){
	HAL_GPIO_WritePin(DISPLAY_E_GPIO_Port, DISPLAY_E_Pin, state ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

static void setF(bool state){
	HAL_GPIO_WritePin(DISPLAY_F_GPIO_Port, DISPLAY_F_Pin, state ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

static void setG(bool state){
	HAL_GPIO_WritePin(DISPLAY_G_GPIO_Port, DISPLAY_G_Pin, state ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

static void printDigit(uint8_t val){
	setA(segmentValues[val][0]);
	setB(segmentValues[val][1]);
	setC(segmentValues[val][2]);
	setD(segmentValues[val][3]);
	setE(segmentValues[val][4]);
	setF(segmentValues[val][5]);
	setG(segmentValues[val][6]);
}
