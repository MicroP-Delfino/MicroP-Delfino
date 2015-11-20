/*
 * F28377S_LaunchPad.h
 *
 *  Created on: Nov 5, 2015
 *      Author: Raz Aloni
 */

#ifndef F28377S_LAUNCHPAD_H_
#define F28377S_LAUNCHPAD_H_

typedef enum
{
	NONE = 0x0,
	RED = 0x1,
	BLUE = 0x2,
	BOTH = 0x3
} leds;

/* Set the LEDS on the built in launchpad */
void LaunchPadLEDS(leds leds);

#endif /* F28377S_LAUNCHPAD_H_ */
