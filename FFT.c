#include <math.h>
#include "FFT.h"

 // struct compx s[FFT_N]; //FFT输入和输出:从S[0]开始存放，根据大小自己定义


  
  struct compx EE(struct compx a,struct compx b)
  {
    struct compx c;
    c.real= a.real*b.real-a.imag*b.imag;
    c.imag= a.real*b.imag+ a.imag*b.real;
    return(c);
  }
  

void create_sin_tab(float *sin_t)
{
   int i;
  for(i=0;i<=FFT_N/4;i++)
  sin_t[i] = sin(2*PI*i/FFT_N);
}

  float sin_tab(float pi,float *SIN_TAB)
  {
  int n;
  float a;
  n=(int)(pi*FFT_N/2/PI);
  if(n>=0&&n<=FFT_N/4)
  a=SIN_TAB[n];
  else if(n> FFT_N/4&&n<FFT_N/2)
  {
    n-=FFT_N/4;
    a=SIN_TAB[FFT_N/4-n];
  }
  else if(n>=FFT_N/2&&n<3*FFT_N/4)
  {     n-=FFT_N/2;
    a=-SIN_TAB[n];
  }
  else if(n>=3*FFT_N/4&&n<3*FFT_N)
  {
    n=FFT_N-n;
    a=-SIN_TAB[n];
  }
  return a;
  }
  
float cos_tab(float pi,float *SIN_TAB)
{
  float a,pi2;
  pi2=pi+PI/2;
  if(pi2>2*PI)
  pi2-=2*PI;
  a=sin_tab(pi2,SIN_TAB);
  return a;
}

  void FFT(struct compx *xin,float *SIN_TAB)
  {
    int f,m,i,k,I,j=0;
    struct compx u,w,temp;
    double t;
    for(i=0;i<FFT_N;i++)
    {
      k=i;j=0;
       t=(log(FFT_N)/log(2));
    while( (t--)>0 )    //利用按位与以及循环实现码位颠倒
    {
          j=j<<1;
          j|=(k & 1);
          k=k>>1;
    }
    if(j>i)    //将x(n)的码位互换
    {
          temp=xin[i];
          xin[i]=xin[j];
          xin[j]=temp;
    }
      }
    {
    int le,lei,ip; //FFT运算核心，使用蝶形运算完成FFT运算
    f=FFT_N;
    for(I=1;(f=f/2)!=1;I++); //计算I的值，即计算蝶形级数
    for(m= 1;m<=I;m++)          //控制蝶形结级数
    {                       //m表示第m级蝶形, |为蝶形级总数l=log (2) N
      le=2<<(m-1);         //le蝶形结距离，即第m级蝶形的蝶形结相距le点
                        //le=pow(2,m);
      lei=le/2;           //同一蝶形结中参加运算的两点的距离
      u.real=1.0; //u为蝶形结运算系数，初始值为1
      u.imag=0.0;
      //w.real=cos(Pl/lei); //不适用查表法计算sin值和cos值
      // w.imag= -sin(Pl/lei);
      w.real=cos_tab(PI/lei,SIN_TAB); //w为系数商，即当前系数与前一个系数的商
      w.imag=-sin_tab(PI/lei,SIN_TAB);
      for(j=0;j<=lei-1;j++) //控制计算不同种蝶形结,即计算系数不同的蝶形结
      {
        for(i=j;i<=FFT_N-1;i=i+le) //控制同-蝶形结运算，即计算系数相同蝶形结
        {
          ip=i+lei; //i, ip分别表示参加蝶形运算的两个节点
          temp=EE(xin[ip],u); //蝶形运算，详见公式
      xin[ip].real=xin[i].real-temp.real;
      xin[ip].imag=xin[i].imag- temp.imag;
      xin[i].real=xin[i].real+temp.real;
      xin[i].imag=xin[i].imag+ temp.imag;
    }
  u=EE(u,w); //改变系数，进行下一个蝶形运算
  }
  }
  }
  }






  void fft_2(unsigned int *zhi,float *mo,float *SIN_TAB)
  {
      int i;
      struct compx s[FFT_N];
      create_sin_tab(SIN_TAB);
      for(i=0;i<FFT_N;i++) //给结构体赋值
      { 
       // s[i].real=sin(2*PI*i/FFT_N); //实部为正弦波FFT_N点采样，赋值为1
        s[i].real=zhi[i];
		s[i].imag=0; //虚部为0
      }
      FFT(s,SIN_TAB); //进行快速福利叶变换
      for(i=0;i<FFT_N;i++) //求变换后结果的模值，存入复数的实部部分
      mo[i]=sqrt((double)(s[i].real*s[i].real+ s[i].imag*s[i].imag));
}



