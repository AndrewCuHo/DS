#ifndef _FIR_H_
#define _FIR_H_


#include <stdint.h>
#include <stdbool.h>

#define samples 10000
#define taps 40


extern float coefficients[taps];
extern float state[taps+1];


extern void fir(uint32_t *input,float *output);
extern float fir_filt(float x,  float *b, float *s);






#endif
