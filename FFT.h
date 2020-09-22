#ifndef _FFT_H_
#define _FFT_H_
//ʹ��ʱӦ����ȫ�ֱ���
/*
	float SIN_TAB[FFT_N/4+1]; //�������ұ�Ĵ�ſռ�
	unsigned int  zhi[FFT_N];  //����Ĳ���ֵ
	float mo[FFT_N];  //����ķ�ֵ
*/

//��ֹ��ջ������ɽ��м����struct compx s[FFT_N];����Ϊȫ�ֱ���������Ҫ�õ�fft����λ����뵥������
		   

#define FFT_N 128 //���帣��Ҷ�任�ĵ���
#define PI 3.1415926535897932384626433832795028841971 //����Բ����ֵ

struct compx {float real,imag;}; //����һһ�������ṹ
struct compx EE(struct compx a,struct compx b);
void create_sin_tab(float *sin_t);
float sin_tab(float pi,float *SIN_TAB);
float cos_tab(float pi,float *SIN_TA);
void FFT(struct compx *xin,float *SIN_TAB);
void fft_2(unsigned int *zhi,float *mo,float *SIN_TAB);   //ʹ��ʱֻ��Ҫ���øú�������

    


#endif