/*
 * display7seg.h
 *
 *  Created on: Dec 20, 2020
 *      Author: hp
 */

#ifndef INC_DISPLAY7SEG_H_
#define INC_DISPLAY7SEG_H_

#include <stdint.h>
#include <stdbool.h>

/* @brief Start hardware timer interrupt routine
 *
 */
void display7segInit(void);

/* @brief Enables display digits
 * @param enable display on
 */
void display7Enable(bool enable);

/* @brief Stores value in RAM and prints on digits
 * @param value to print {0 .. 99}
 */
void display7segWrite(uint8_t num);

/* @brief Interrupt Handler routine
 *
 */
void display7segInterruptHandler(void);

#endif /* INC_DISPLAY7SEG_H_ */
