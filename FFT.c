#include <math.h>
#include "FFT.h"

 // struct compx s[FFT_N]; //FFT��������:��S[0]��ʼ��ţ����ݴ�С�Լ�����


  
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
    while( (t--)>0 )    //���ð�λ���Լ�ѭ��ʵ����λ�ߵ�
    {
          j=j<<1;
          j|=(k & 1);
          k=k>>1;
    }
    if(j>i)    //��x(n)����λ����
    {
          temp=xin[i];
          xin[i]=xin[j];
          xin[j]=temp;
    }
      }
    {
    int le,lei,ip; //FFT������ģ�ʹ�õ����������FFT����
    f=FFT_N;
    for(I=1;(f=f/2)!=1;I++); //����I��ֵ����������μ���
    for(m= 1;m<=I;m++)          //���Ƶ��νἶ��
    {                       //m��ʾ��m������, |Ϊ���μ�����l=log (2) N
      le=2<<(m-1);         //le���ν���룬����m�����εĵ��ν����le��
                        //le=pow(2,m);
      lei=le/2;           //ͬһ���ν��вμ����������ľ���
      u.real=1.0; //uΪ���ν�����ϵ������ʼֵΪ1
      u.imag=0.0;
      //w.real=cos(Pl/lei); //�����ò������sinֵ��cosֵ
      // w.imag= -sin(Pl/lei);
      w.real=cos_tab(PI/lei,SIN_TAB); //wΪϵ���̣�����ǰϵ����ǰһ��ϵ������
      w.imag=-sin_tab(PI/lei,SIN_TAB);
      for(j=0;j<=lei-1;j++) //���Ƽ��㲻ͬ�ֵ��ν�,������ϵ����ͬ�ĵ��ν�
      {
        for(i=j;i<=FFT_N-1;i=i+le) //����ͬ-���ν����㣬������ϵ����ͬ���ν�
        {
          ip=i+lei; //i, ip�ֱ��ʾ�μӵ�������������ڵ�
          temp=EE(xin[ip],u); //�������㣬�����ʽ
      xin[ip].real=xin[i].real-temp.real;
      xin[ip].imag=xin[i].imag- temp.imag;
      xin[i].real=xin[i].real+temp.real;
      xin[i].imag=xin[i].imag+ temp.imag;
    }
  u=EE(u,w); //�ı�ϵ����������һ����������
  }
  }
  }
  }






  void fft_2(unsigned int *zhi,float *mo,float *SIN_TAB)
  {
      int i;
      struct compx s[FFT_N];
      create_sin_tab(SIN_TAB);
      for(i=0;i<FFT_N;i++) //���ṹ�帳ֵ
      { 
       // s[i].real=sin(2*PI*i/FFT_N); //ʵ��Ϊ���Ҳ�FFT_N���������ֵΪ1
        s[i].real=zhi[i];
		s[i].imag=0; //�鲿Ϊ0
      }
      FFT(s,SIN_TAB); //���п��ٸ���Ҷ�任
      for(i=0;i<FFT_N;i++) //��任������ģֵ�����븴����ʵ������
      mo[i]=sqrt((double)(s[i].real*s[i].real+ s[i].imag*s[i].imag));
}



