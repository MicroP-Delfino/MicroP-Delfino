/*
 * PCM3002.c
 *
 *  Created on: Nov 9, 2015
 *      Author: Raz Aloni
 */

#include "PCM3002.h"

#ifndef	SYSCLK_FRQ_MHZ
#define SYSCLK_FRQ_MHZ 10.0
#endif

#ifndef LSPCLK_FRQ_MHZ
#define LSPCLK_FRQ_MHZ SYSCLK_FRQ_MHZ/4.0
#endif

/* Max SPI speed = 10 MHz */
#define PCM3002_MAX_SPICLK 10.0

const unsigned int SPICLKDIV = (PCM3002_MAX_SPICLK * 4 >= LSPCLK_FRQ_MHZ) ? 0 					// If LSPCLK/4 is less than or equal to SPI clock max speed, default to 0
								: (unsigned int)(LSPCLK_FRQ_MHZ/PCM3002_MAX_SPICLK + 0.5) - 1;	// SPI Baud div = ceil(LSPCLK frequency/ max speed) - 1

static void InitSPI();
static void InitMcBSP();

/* Initializes the PCM3002 Codec */
void PCM3002_Init()
{
	// TODO: Implement the following functions
	InitSPI();
	InitMcBSP();

	// TODO: Configure PCM3002

};

/* Send a stero signal to the DAC */
void PCM3002_Send(StereoSignal s)
{
	// TODO: Send Stereo Signal through McBSP
}

/* Receive a stereo signal from the ADV */
StereoSignal PCM3002_Receive()
{
	// TODO: Receive Sterio Signal from McBSP
	StereoSignal r = {0,0};
	return r;
}

/* Configure the registers of the ADC */
int PCM3002_SWConfigure(PCM3002_Register reg)
{
	while(SpibRegs.SPISTS.bit.BUFFULL_FLAG); // Wait until buffer can take in values
	SpibRegs.SPITXBUF = *(unsigned int *)&reg;
	return 0;
}


/* Initializes SPI at GPIO 58 (SPICLKB), 59 (SPISTEB), 60 (SPISIMOB)*/
static void InitSPI()
{
	EALLOW;

	GpioCtrlRegs.GPBGMUX2.bit.GPIO58 = 0x1;
	GpioCtrlRegs.GPBGMUX2.bit.GPIO59 = 0x1;
	GpioCtrlRegs.GPBGMUX2.bit.GPIO60 = 0x1;

	GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0x2;
	GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 0x2;
	GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 0x2;

	CpuSysRegs.PCLKCR8.bit.SPI_B = 1;				// Enable SPIB Clk

	SpibRegs.SPICCR.bit.SPISWRESET = 0;				// Set SPI into reset mode
	SpibRegs.SPICCR.bit.CLKPOLARITY = 1;			// Data is output on falling edge (PCM3002 will read on following rising edge)
	SpibRegs.SPICCR.bit.SPICHAR = 0xF;				// 16 bit words
	SpibRegs.SPICTL.bit.MASTER_SLAVE = 1;			// SPI Master
	SpibRegs.SPIBRR.bit.SPI_BIT_RATE = SPICLKDIV;	// 10 Mbit/s or less
	SpibRegs.SPIPRI.bit.FREE = 1;					// SPI operation will continue through breakpoints
	SpibRegs.SPIPRI.bit.TRIWIRE = 1;				// Three wire mode (SIMO becomes MIMO, but input isnt used anyways)
	SpibRegs.SPICTL.bit.TALK = 1;					// Enable output
	SpibRegs.SPICCR.bit.SPISWRESET = 1;				// Take out of reset mode

	EDIS;
}

/* Initializes McBSP at <> */
static void InitMcBSP()
{
	// TODO: Init McBSP
}
