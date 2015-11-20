/*
 * main.c
 */

#include "F2837xS_device.h"
#include "PCM3002.h"
#include "Configurations.h"

void EnableFullClockSpeed();

int main(void)
{
	// Disable WD Timer
	EALLOW;
	WdRegs.WDCR.bit.WDDIS = 1;
	EDIS;

	EnableFullClockSpeed();

	// Initialize PCM3002 Codec
	PCM3002_Init();

	PCM3002_Register config;
	config.reg0 =  (PCM3002_Register0)PCM3002_REG0_DEFAULT;

	PCM3002_SWConfigure(config);

	while(1)
	{
		for(int i = 0; i < 20000; i++)
		{
			config.reg0.AL--;
			PCM3002_SWConfigure(config);
		}
	}
}

void EnableFullClockSpeed()
{
	// TODO: Fix clocking
	EALLOW;

	ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF = 0;
	ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1; // External oscilator

	/* Set PLL Multiplies */
	ClkCfgRegs.SYSPLLMULT.bit.FMULT = 0;	// Fractional multiplier = 0
	ClkCfgRegs.SYSPLLMULT.bit.IMULT = SYSCLK_FRQ_MHZ/5.0;	// Integer multiplier = Sysclk / 5;

	ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 1;	// No divide into PLLSYSCLK

	/* Enable PLL */
	ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 1; // Enable PLL

	while(!ClkCfgRegs.SYSPLLSTS.bit.LOCKS); // Wait until PLL is locked

	ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1; // Mux select

	asm(" RPT #100 || NOP"); // Delay

	EDIS;
}
