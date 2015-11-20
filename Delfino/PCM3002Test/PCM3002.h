/*
 * PCM3002.h
 *
 *  Created on: Nov 9, 2015
 *      Author: Raz Aloni
 */

#ifndef PCM3002_H_
#define PCM3002_H_

#include "F2837xS_device.h"
#include "Configurations.h"

#define PCM3002_REG0_DEFAULT {.res = 0, .Addr = 0, .LDL = 0, .AL = 0xFF}
#define PCM3002_REG1_DEFAULT {.res = 0, .Addr = 1, .LDR = 0, .AR = 0xFF}
#define PCM3002_REG2_DEFAULT {.res = 0, .Addr = 2, .PDAD = 0, .BYPS = 0, .PDDA = 0, .ATC = 0, .IZD = 0, .OUT = 0, .DEM = 1, .MUT = 0}
#define PCM3002_REG3_DEFAULT {.res = 0, .Addr = 3, .res2 = 0, .LOP = 0, .res3 = 0, .FMT = 0, .LRP = 0, .res4 = 0}

	typedef struct
	{
		long left;
		long right;
	} StereoSignal;

	typedef struct
	{
		unsigned int AL	  : 8;
		unsigned int LDL  : 1;
		unsigned int Addr : 2;
		unsigned int res  : 5;
	} PCM3002_Register0;

	typedef struct
	{
		unsigned int AR	  : 8;
		unsigned int LDR  : 1;
		unsigned int Addr : 2;
		unsigned int res  : 5;
	} PCM3002_Register1;

	typedef struct
	{
		unsigned int MUT  : 1;
		unsigned int DEM  : 2;
		unsigned int OUT  : 1;
		unsigned int IZD  : 1;
		unsigned int ATC  : 1;
		unsigned int PDDA : 1;
		unsigned int BYPS : 1;
		unsigned int PDAD : 1;
		unsigned int Addr : 2;
		unsigned int res  : 5;
	} PCM3002_Register2;

	typedef struct
	{
		unsigned int res4 : 1;
		unsigned int LRP  : 1;
		unsigned int FMT  : 2;
		unsigned int res3 : 1;
		unsigned int LOP  : 1;
		unsigned int res2 : 3;
		unsigned int Addr : 2;
		unsigned int res  : 5;
	} PCM3002_Register3;

	typedef union
	{
		PCM3002_Register0 reg0;
		PCM3002_Register1 reg1;
		PCM3002_Register2 reg2;
		PCM3002_Register3 reg3;
	} PCM3002_Register;

	/* Initializes the PCM3002 Codec */
	void PCM3002_Init();

	/* Send a stero signal to the DAC */
	void PCM3002_Send(StereoSignal s);

	/* Receive a stereo signal from the ADV */
	StereoSignal PCM3002_Receive();

	/* Configure the registers of the ADC */
	int PCM3002_SWConfigure(PCM3002_Register reg);

#endif /* PCM3002_H_ */
