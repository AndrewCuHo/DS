/*
 * feature extraction.c
 *
 *  Created on: 2019年8月2日
 *  Author: 09050220
 */
#include "extraction.h"
#include <stdlib.h>
#include <math.h>

void data_process(float *data, float *feature)
{
  unsigned char i,number;
  float sum,avg;
  float spow,imax,imin;
  number = FFT_N/2+1;
  for(i=0;i<number;i++)
  {
    sum = sum + data[i];
  }
  avg = sum/number;
  for(i=0;i<number;i++)
  {
    spow = spow + (data[i]-avg)*(data[i]-avg);
  }
  feature[0] = sum;//和
  feature[1] = avg;//平均值
  feature[2] = spow;//方差
  
  for(i=0;i<number;i++)
  {
    if(data[i]>imax)
        {
            imax=data[i];
        }
        if(data[i]<imin)
        {
            imin=data[i];
        }
  }
  feature[3] = imax;//最大值
  feature[4] = imin;//最小值
  feature[5] = imax - imin;//范围
  for(i=0;i<number;i++)
  {
    data[i] = (data[i]-imin)/feature[5];
  }
}

void frequency_extraction(float *mo, float *feature)
{
  unsigned char i,number;
  float sum=0,avg=0;
  float spow=0,skewness=0,kurtosis=0;
  number = FFT_N/2+1;
  feature[0] = mo[0];//直流分量
  for(i=0;i<number;i++)
  {
    sum = sum + mo[i];
  }
  avg = sum/number;
  for(i=0;i<number;i++)
  {
    spow = spow + (mo[i]-avg)*(mo[i]-avg);
  }
  spow = sqrt(spow);
  feature[1] = sum / 10000;//和
  feature[2] = spow / 10000;//方差
  for(i=0;i<number;i++)
  {
    skewness = skewness + ((mo[i] - avg)/spow)*((mo[i] - avg)/spow)*((mo[i] - avg)/spow);
  }
  feature[3] = skewness / number;//偏度
  for(i=0;i<number;i++)
  {
    kurtosis = kurtosis + ((mo[i] - avg)/spow)*((mo[i] - avg)/spow)*((mo[i] - avg)/spow)*((mo[i] - avg)/spow);
  }
  feature[4] = kurtosis / number - 3;//风度
  
}

