#include <msp430f5529.h>
#include "msp_ad.h"


void ad_init(void)
{
  P6SEL |= 0X01;  //使能A0采样通道
  ADC12CTL0 = ADC12ON+ADC12SHT0_8+ADC12MSC;
  ADC12CTL1=ADC12SHP+ADC12CONSEQ_2;
  ADC12IE=0X01;
  ADC12CTL0 |= ADC12ENC;
  ADC12CTL0 |= ADC12SC;//启动转换
  __bis_SR_register(GIE);
  
  
}