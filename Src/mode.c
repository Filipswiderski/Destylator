/*
 * mode.c
 *
 *  Created on: Dec 29, 2020
 *      Author: hp
 */

#include "mode.h"

static bool displayBlink;


void modeSettings(void) {
	displayBlink = true;
}

void modeDisplay(void) {
	displayBlink = false;
}

bool modeGet(void) {
	return displayBlink;
}
