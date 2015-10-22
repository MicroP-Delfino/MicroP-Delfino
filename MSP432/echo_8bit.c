
//Daniel Kelly
//10/21/2015
//MSP432P401R Echo Program Example
/*******************
This program configures a set of 8 pins as inputs and 8 pins as outputs
and echoes the input pattern on the input pins to the output pins.

For input pins, the program configures P5.0:P5.2, P5.4:P5.7, and P6.0.
For output pins, the program configures P4.0:P4.7.
These pins were chosen due to them being broken out on the MSP432P401R launchpad.
********************/

#include "msp.h"

void main(void)
{

	int input = 0;

    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer

    //The following code configures P5.0:P5.2, P5.4:P5.7, and P6.0 as General Purpose I/O by setting select bits to 0.
    P5SEL1 &= 0x0000100;		//Set pins P5.0:P5.7 (excluding P5.3) as GPIO
    P5SEL0 &= 0x0000100;

    P6SEL1 &= BIT0;			//Set pin P6.0 as GPIO
    P6SEL0 &= BIT0;

    //The following code configure P4.0:P4.7 as General Purpose I/O by setting select bits to 0.
    P4SEL1 &= 0;
    P4SEL0 &= 0;

    //The following code configures P5.0:P5.2, P5.4:P5.7, and P6.0 as as inputs by setting the direction bits to 0.
    P5DIR &= 0x0000100;
    P6DIR &= BIT0;

    //The following code configures P4.0:P4.7 as outputs by setting the direction bits to 1.
    P4DIR |= 0xFF;

    //The following while loop reads in the input pins, and sends the values out to the output pins. This is the echo part of the program.
    //The loop is echoing (in order of most significant bit), P6.0 to P4.7, P5.7:P5.4 to P4.6:P4.3, P5.2:P5.0 to P4.2:P4.0
    while(1)
    {
    	int temp = (P6IN & 0x1) << 7;				//Read P6.0 and shift the bit over by 7
    	int temp2 = P5IN & 0xF7;					//Read Port 5 and cancel out P5.3 (since we are not using that pin)
    	input = temp | ((temp2 & 0xF0) >> 1) | (temp2 & 0xF); //Take high 4 bits of temp2 and shift them over by 1. Then OR this with the lower 4 values of temp2 and the value of P6.0

    	P4OUT = input;							//Send the resulting value to Port 4, effectively echoing in what was read.

    }

}
