
#include "F28x_Project.h"     // Device Headerfile and Examples Include File

void main(void)
{
    DisableDog();

    EALLOW;

    GpioCtrlRegs.GPALOCK.all = 0x00000000;	//unlock all GPIO port A

    GpioCtrlRegs.GPAGMUX1.all = 0x00000000; //set gpio A port to be general I/O
    GpioCtrlRegs.GPAMUX1.all = 0x0000000;   //set gpio A port to be general I/O

    GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;	// GPIO2 = output
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;	// GPIO3 = input

    EDIS;

    while(1)
    {
    	GpioDataRegs.GPADAT.bit.GPIO2 = GpioDataRegs.GPADAT.bit.GPIO3; //echo bit from input to output
    }
}
