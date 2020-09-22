#ifndef _FFT_H_
#define _FFT_H_
//使用时应定义全局变量
/*
	float SIN_TAB[FFT_N/4+1]; //定义正弦表的存放空间
	unsigned int  zhi[FFT_N];  //输入的采样值
	float mo[FFT_N];  //输出的幅值
*/

//防止堆栈溢出，可将中间变量struct compx s[FFT_N];定义为全局变量，如需要用到fft求相位则必须单独定义
		   

#define FFT_N 128 //定义福利叶变换的点数
#define PI 3.1415926535897932384626433832795028841971 //定义圆周率值

struct compx {float real,imag;}; //定义一一个复数结构
struct compx EE(struct compx a,struct compx b);
void create_sin_tab(float *sin_t);
float sin_tab(float pi,float *SIN_TAB);
float cos_tab(float pi,float *SIN_TA);
void FFT(struct compx *xin,float *SIN_TAB);
void fft_2(unsigned int *zhi,float *mo,float *SIN_TAB);   //使用时只需要调用该函数即可

    


#endif