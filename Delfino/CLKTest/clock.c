/*
 * clock.c
 *
 *  Created on: Nov 5, 2015
 *      Author: Raz Aloni
 */

#include "clock.h"
#include "F2837xS_device.h"

/* Initialize the system clock */
CLK_RESULT setSysClk(unsigned int Freq, CLK_SRC clock, unsigned int extFreq)
{
	// Calculate frequency multipliers and dividers
	float mult = (float)Freq/(float)extFreq;

	unsigned int multi = (unsigned int)mult;

	EALLOW;

	if (clock == ExternalOsc)
	{
		// If using external oscillator, then enable the oscillator
		ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF = 0;
	}

	// Set Source
	ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = clock;

	EDIS;

	return Success;
}
