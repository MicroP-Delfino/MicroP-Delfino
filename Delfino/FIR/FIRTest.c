/*
 * FIRTest.c
 *
 *  Created on: Nov 5, 2015
 *      Author: Raz Aloni
 */

#include "F28x_Project.h"
#include "fir.h"
#include "FIRCoefficients2.h"
#include "testSignal.h"
#include "F28377S_LaunchPad.h"
#include <math.h> // For creating a sinusoid

#define FilterOrder FILTER_TAP_NUM - 1

#if FILTER_TAP_NUM % 2 == 0
#define FIRTaps FILTER_TAP_NUM
#else
#define FIRTaps FILTER_TAP_NUM + 1
#endif

#define EnableProbePin() EALLOW; \
	GpioCtrlRegs.GPCMUX1.bit.GPIO71 = 0; \
	GpioCtrlRegs.GPCDIR.bit.GPIO71 = 1; \
	GpioDataRegs.GPCCLEAR.bit.GPIO71 = 1; \
	EDIS

#define ProbeHigh() EALLOW; \
	GpioDataRegs.GPCSET.bit.GPIO71 = 1; \
	EDIS

#define ProbeLow() EALLOW; \
	GpioDataRegs.GPCCLEAR.bit.GPIO71 = 1; \
	EDIS

#define ProbeToggle() EALLOW; \
	GpioDataRegs.GPCTOGGLE.bit.GPIO71 = 1; \
	EDIS

/*
 * Delay buffer needs to be aligned on a 256 word boundary (has to do with the C28x circular buffer functionality)
 */
#pragma DATA_SECTION(circularBuffer, "delayBuffer")
long circularBuffer[FIRTaps/2];

/*
 *  Reloacte input and output arrays
 */
#pragma DATA_SECTION(testSignal, "ramgs0")
int testSignal[DEFAULT_SIGNAL_LENGTH];

#pragma DATA_SECTION(resultSignal, "ramgs1")
int resultSignal[DEFAULT_SIGNAL_LENGTH];

void reorgCoefficients(const int * normalOrder, int * revisedOrder, int size);
interrupt void WakeUp_ISR();

// Check if awake has been triggered.
unsigned int awake = 0;

int main()
{
	// Disable WatchDog, set GPIO to be pulled high (saves power), enable peripheral clocks, and set SysCLK to 200 MHz
	DisableDog();
	GPIO_EnableUnbondedIOPullups();
	InitSysPll(XTAL_OSC,IMULT_40,FMULT_0,PLLCLK_BY_2); 		//PLLSYSCLK = 10Mhz(OSCCLK) * 40 (IMULT) * 1 (FMULT) /  2 (PLLCLK_BY_2)


	LaunchPadLEDS(BLUE);
	EnableProbePin();


	/* Coefficients to use for filter
	 * Coefficients are 16 bit integers in Q15 format.
	 * The size of the coefficient array needs to be an even number because the FIR algorithm uses DMACs to accomplish
	 * quick convolution.
	 *
	 * If your filter order is even (number of taps is odd), create an array of one size larger and make the last value equal to 0.
	 *
	 * See comment in reorgCoefficients function to see how coefficients need to be ordered.
	 */
	int filterCoefficients[FIRTaps];
	reorgCoefficients(filter_taps, filterCoefficients, FIRTaps);

	if (FILTER_TAP_NUM % 2)
	{
		filterCoefficients[0] = 0;
	}

	/* Initialize a FIR16 module with default values */
	FIR16 firFilterModule = FIR16_DEFAULTS;
	firFilterModule.order = FilterOrder;
	firFilterModule.dbuffer_ptr = &circularBuffer[0];
	firFilterModule.coeff_ptr = (long *)&filterCoefficients[0];	// Coefficients are treated as 32 bit values for DMAC
	firFilterModule.init(&firFilterModule);

	CreateTestSignal(SampleRate, 1300.0, 4000.0, DEFAULT_SIGNAL_LENGTH, testSignal);

	unsigned int i = 0; // Index for accessing arrays

	/* Init Timer1 and interrupt*/
	CpuTimer1.RegsAddr = &CpuTimer1Regs;
	ConfigCpuTimer(&CpuTimer1, 200.0, 1000000/SampleRate);

	DINT;

	InitPieVectTable();
	EALLOW;
	PieVectTable.TIMER1_INT = WakeUp_ISR;

	IER |= M_INT13;
	StartCpuTimer1();

	EDIS;
	EINT;

	IDLE(); // Enter Idle mode to save power

	while(1)
	{
		if (awake)
		{
			ProbeHigh();

			firFilterModule.input = testSignal[i];
			firFilterModule.calc(&firFilterModule);
			resultSignal[i++] = firFilterModule.output;

			ProbeLow();

			if (i == DEFAULT_SIGNAL_LENGTH)
			{
				i = 0; // Loops around 0 to Signal Length
			}

			/* Back to sleep */
			awake = 0;
			IDLE();
		}
	}
}

interrupt void WakeUp_ISR()
{
	if (awake)
	{
		return;	// If already awake, return
	}

	awake = 1;
};

void reorgCoefficients(const int * normalOrder, int * revisedOrder, int size)
{
	/*
	 * Coefficients should be ordered like so:
	 * Index     LSW 	   MSW
	 * 	 	 +---------+---------+
	 * 0 	 | h(L-1)  | h(L/2-1)|
	 * 2 	 | h(L-2)  | h(L/2-2)|
	 * 4 	 | h(L-3)  | h(L/2-3)|
	 * 6 	 | h(L-4)  | h(L/2-4)|
	 * ... 	 | ...     | ...     |
	 * L-6 	 | h(L/2+2)| h(2) 	 |
	 * L-4   | h(L/2+1)| h(1) 	 |
	 * L-2   | h(L/2)  | h(0) 	 |
	 * 		 +---------+---------+
	 */

	for(int i = 0; i < size; i += 2)
	{
		revisedOrder[size-i-2] = normalOrder[i/2+size/2];
		revisedOrder[size-i-1] = normalOrder[i/2];
	}
}
