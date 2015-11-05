/*
 * CLKTest.c
 *
 *  Created on: Nov 4, 2015
 *      Author: Raz Aloni
 */

#include "F2837xS_device.h"

int main(void)
{
	EALLOW;

	/* Disable WatchDog Timer */
	WdRegs.WDCR.bit.WDDIS = 1;

	ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1; // External oscilator

	/* Set PLL Multiplies */
	ClkCfgRegs.SYSPLLMULT.bit.FMULT = 0;	// Fractional multiplier = 0
	ClkCfgRegs.SYSPLLMULT.bit.IMULT = 1;	// Integer multiplier = 1;

	ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0;	// No divide into PLLSYSCLK

	/* Enable PLL */
 	ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 1; // Enable PLL

	while(!ClkCfgRegs.SYSPLLSTS.bit.LOCKS); // Wait until PLL is locked

	ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1; // Mux select

	asm(" RPT #100 || NOP"); // Delay

	/* Set GPIO73 to XCLKOut for PLLSYSCLK */
	GpioCtrlRegs.GPCGMUX1.bit.GPIO73 = 0;
	GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 3;

	ClkCfgRegs.XCLKOUTDIVSEL.bit.XCLKOUTDIV = 0;	// No divide on XCLK

	/* Set GPIO13 (Blue LED on launchpad) */
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;

	/* Turn off Red LED */
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;
	GpioDataRegs.GPASET.bit.GPIO12 = 1;

	EDIS;

	/* Test initial clock speed */
	while(1)
	{
		GpioDataRegs.GPATOGGLE.bit.GPIO13 = 1;
	}
}


