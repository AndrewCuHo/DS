#ifndef _extraction_H_
#define _extraction_H_
#include "FFT.h"
//使用时应定义全局变量
/*
data_process     输出:0.和 1.平均值 2.方差 3.最大值 4.最小值 5.范围  
frequency_extraction     输出:0. 直流分量 1.和 2.方差 3.偏度 4.峰度 
*/
   

void data_process(float *data, float *feature); //采集的ad传入得到时域统计信息  
void frequency_extraction(float *mo, float *feature);    //fft得到的模传入得到频域统计信息 


#endif