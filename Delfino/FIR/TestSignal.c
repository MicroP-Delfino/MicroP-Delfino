/*
 * TestSignal.c
 *
 *  Created on: Nov 19, 2015
 *      Author: Raz Aloni
 */

#include <math.h>

void CreateTestSignal(float SamplingRate, float SinusoidFreq1, float SinusoidFreq2, unsigned int signalLength, int* signal)
{
	for(int i = 0; i < signalLength; i++)
	{
		signal[i] = (int)((0.5 * sin(2 * 3.14 * SamplingRate/SinusoidFreq1 * i) + 0.5 * sin(2* 3.14 * SamplingRate/SinusoidFreq2 * i + 1)) * 32768);
	}
}


