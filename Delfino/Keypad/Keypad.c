/*
 * Keypad.c
 *
 *  Created on: Oct 8, 2015
 *      Author: Raz Aloni
 */

#include "Keypad.h"

void InitKeypad()
{
	EALLOW;

	// Disable locks (done by default) and set all gpio inputs to have internal pullups enabled
	//InitGpio();

	/*
	 * Keypad will be located on pins 12-19
	 * Pins 15-12 will correspond to the columns of the keypad (pins 1-4) and will be outputs
	 * Pins 19-16 will correspond to the rows of the keypad (pins 5-8) and will be inputs pulled high
	 */

	// Set inputs/outputs
	GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;		// GPIO19 = input
	GpioCtrlRegs.GPADIR.bit.GPIO18 = 0; 	// GPIO18 = input
	GpioCtrlRegs.GPADIR.bit.GPIO17 = 0; 	// GPIO17 = input
	GpioCtrlRegs.GPADIR.bit.GPIO16 = 0; 	// GPIO16 = input
	GpioCtrlRegs.GPADIR.bit.GPIO15 = 1; 	// GPIO15 = output
	GpioCtrlRegs.GPADIR.bit.GPIO14 = 1; 	// GPIO14 = output
	GpioCtrlRegs.GPADIR.bit.GPIO13 = 1; 	// GPIO13 = output
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 1; 	// GPIO12 = output

	// Give inputs internal pullups
	GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;

	// Setup input qualification (avoid bounce)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 2;			// Six sample qualification for pins 19-16
	GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 2;
	GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 2;
	GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 2;
	GpioCtrlRegs.GPACTRL.bit.QUALPRD2 = 0;			// Sample period = PLLSYSCLK

	// Set Outputs to all high
	GpioDataRegs.GPASET.all = 0x0000F000;
}

int ReadKeypad()
{
	// To hold keypad value
	int kpResult;

	// Value used to toggle the column being checked
	unsigned int toggle = 0x0000C000;

	// Clear bit 1, set bits 2-4
	GpioDataRegs.GPACLEAR.all = 0x00008000;
	GpioDataRegs.GPASET.all = 0x00007000;

	int i;
	for (i = 0; i < 4; i++)
	{
		// Get input results, mask out other values and shift right
		kpResult = (GpioDataRegs.GPADAT.all & 0x000F0000) >> 16;

		// Check to see if we got a value
		switch(kpResult)
		{
			case 0xF:	break;	//If value is 0xF, button was not pressed in this row. Continue
			case 0x7:	return (i == 3) ? 0xA : i+1;	// 1st row result (1,2,3,A)
			case 0xB:	return (i == 3) ? 0xB : i+4;	// 2nd row result (4,5,6,B)
			case 0xD:	return (i == 3) ? 0xC : i+7;	// 3rd row result (7,8,9,C)
			case 0xE:									// 4th row result (*,0,#,D)
				switch(i)
				{
					case 0: return 0xE;
					case 1: return 0;
					case 2:	return 0xF;
					case 3: return 0xD;
				}
		}

		// Value not found, toggle pins
		GpioDataRegs.GPATOGGLE.all = toggle;

		// Shift toggle right 1
		toggle = toggle >> 1;
	}

	// No valid button press, return -1
	return -1;
}


