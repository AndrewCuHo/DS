#include <msp430f5529.h>
#include "msp_ad.h"


void ad_init(void)
{
  P6SEL |= 0X01;  //ʹ��A0����ͨ��
  ADC12CTL0 = ADC12ON+ADC12SHT0_8+ADC12MSC;
  ADC12CTL1=ADC12SHP+ADC12CONSEQ_2;
  ADC12IE=0X01;
  ADC12CTL0 |= ADC12ENC;
  ADC12CTL0 |= ADC12SC;//����ת��
  __bis_SR_register(GIE);
  
  
}