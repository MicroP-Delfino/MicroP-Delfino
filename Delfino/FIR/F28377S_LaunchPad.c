/*
 * F28377S_LaunchPad.c
 *
 *  Created on: Nov 5, 2015
 *      Author: Raz Aloni
 */

#include "F28377S_LaunchPad.h"
#include "F2837xS_device.h"

/* Set the LEDS on the built in launchpad */
void LaunchPadLEDS(leds leds)
{
	EALLOW;

	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;
	GpioDataRegs.GPASET.bit.GPIO12 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;
	GpioDataRegs.GPASET.bit.GPIO13 = 1;

	if(leds & 1)
	{
		GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;
	}

	if(leds & 2)
	{
		GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;
	}

	EDIS;
}
