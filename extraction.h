#ifndef _extraction_H_
#define _extraction_H_
#include "FFT.h"
//ʹ��ʱӦ����ȫ�ֱ���
/*
data_process     ���:0.�� 1.ƽ��ֵ 2.���� 3.���ֵ 4.��Сֵ 5.��Χ  
frequency_extraction     ���:0. ֱ������ 1.�� 2.���� 3.ƫ�� 4.��� 
*/
   

void data_process(float *data, float *feature); //�ɼ���ad����õ�ʱ��ͳ����Ϣ  
void frequency_extraction(float *mo, float *feature);    //fft�õ���ģ����õ�Ƶ��ͳ����Ϣ 


#endif