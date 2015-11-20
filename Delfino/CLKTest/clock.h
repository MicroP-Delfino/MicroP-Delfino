/*
 * clock.h
 *
 *  Created on: Nov 5, 2015
 *      Author: Raz Aloni
 */

#ifndef CLOCK_H_
#define CLOCK_H_

typedef enum
{
	Success,
	TooFast,
	TooSlow,
	CannotCalc
} CLK_RESULT;

typedef enum
{
	InternalOsc1 = 1,
	InternalOsc2 = 0,
	ExternalOsc = 2
} CLK_SRC;

/* Initialize the system clock */
CLK_RESULT setSysClk(unsigned int freq, CLK_SRC clock, unsigned int extFreq);

#endif /* CLOCK_H_ */
