/*

FIR filter designed with
http://t-filter.appspot.com

sampling frequency: 8000 Hz

fixed point precision: 16 bits

* 0 Hz - 800 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

* 1500 Hz - 2500 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = n/a

* 3200 Hz - 4000 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

*/


#ifndef FIRCOEFFICIENTS_H_
#define FIRCOEFFICIENTS_H_

#define FILTER_TAP_NUM 25
#define SampleRate 8000.0

const int filter_taps[FILTER_TAP_NUM] = {
  46,
  0,
  1020,
  0,
  -3092,
  0,
  2210,
  0,
  6140,
  0,
  -18814,
  0,
  25110,
  0,
  -18814,
  0,
  6140,
  0,
  2210,
  0,
  -3092,
  0,
  1020,
  0,
  46
};

#endif /* FIRCOEFFICIENTS_H_ */
