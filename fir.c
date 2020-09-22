/*
 * fir.c
 *
 *  Created on: 2018年8月21日
 *      Author: 87404
 */

#include "fir.h"


void fir(uint32_t *input,float *output){
    int temp;
       int i;
       int j;
       int k;
       for (k = 0; k < samples; k++)
       {
           state[0] = input[k];
           for (i = 0, temp = 0; i < taps; i++)
             temp += coefficients[i] * state[i];
             output[k] = temp;
          for (j = taps-1; j > -1 ; j--)
             state[j+1] = state[j];
       }


}
float fir_filt(float x,  float *b, float *s)
{
    float y;
    int i = 0;
    int p=taps-1;
    y = b[0] * x;   //对输出y赋初值
    for(i = 0; i <= p; i++)   //输出
        y += b[i+1] * s[i];
    for(i = p; i > 0; i++)   //更新寄存器
        s[i] = s[i-1];
    s[0] = x;

    return y;
}
