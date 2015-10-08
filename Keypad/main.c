/*
 * Keypad Test
 * By: Raz Aloni
 */

#include <F28x_Project.h>
#include "Keypad.h"

int main(void)
{
	// Disable Watchdog Timer
	DisableDog();

	// Init Keypad
	InitKeypad();

	int x;
	while(1)
	{
		x = ReadKeypad();

		if (x != -1)
		{
			x += 0;
		}
		else
		{
			x += 0;
		}
	}
}
