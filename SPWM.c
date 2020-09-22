/*----------------------------------------------------------------------------------------------
 * 功能：产生单路SPWM波
 * 输入：无
 * 输出：P1.4
 * 注意：定时器也为TA1.1;载波频率为126.26K；；默认正弦频率为100HZ，幅度未知
 */
#include <MSP430.h> 
#include "SPWM.h"
void SPWM_1Way_Init(void)
{
    P1SEL |=BIT4;
    P1DIR |=BIT4;
    //P1DS |=BIT4; //全力驱动
    P1OUT &=~BIT4;
    spwm_i=0;
    TA0CCR0 =9;//载波126.26KHZ
    TA0CCR3 =Lab1[spwm_i];
    TA0CCTL3 =OUTMOD_7;
    TA0CTL =TASSEL_2+MC_1+TACLR;//选择时钟为SMCLK，UP模式

    P2SEL |=BIT0;
    P2DIR |=BIT0;
    P2OUT &=~BIT0;
    TA1CCR0 =2499;//25000000/(100*100)=2500:100Hz，100个点：10KHZ(时间不太准我做了些补偿)
    TA1CTL =TASSEL_2+MC_1+TACLR;//选择时钟为SMCLK，UP模式
    TA1CTL  |= TAIE;//开启中断

    __enable_interrupt();//开启总中断
}
void SPWM_1Way_Set_Freq(unsigned int freq)
{
    unsigned long freq_num;
    freq_num=2500000/(freq)-1;
    TA1CCR0 =freq_num;
}
/*
 * 功能：输出两路SPWM波，相位可调
 * 输入：无
 * 输出：P1.4,P1.5
 * 注意：定时器也为TA1.1;载波频率为126.26K；；默认正弦频率为100HZ，幅度未知
 */
void SPWM_2Way_Init(void)
{
    P1SEL |=BIT4+BIT5;
    P1DIR |=BIT4+BIT5;
    //P1DS |=BIT4+BIT5; //全力驱动
    P1OUT &=~BIT4+BIT5;
    spwm_i=0;
    spwm_j=0;//控制相位
    TA0CCR0 =198;//载波126.26KHZ
    TA0CCR3 =Lab1[spwm_i];
    TA0CCR4 =Lab1[spwm_j];
    TA0CCTL3 =OUTMOD_7;
    TA0CCTL4 =OUTMOD_7;
    TA0CTL =TASSEL_2+MC_1+TACLR;//选择时钟为SMCLK，UP模式

    P2SEL |=BIT0;
    P2DIR |=BIT0;
    P2OUT &=~BIT0;
    TA1CCR0 =2499;//25000000/(100*100)=2500:100Hz，100个点：10KHZ
    TA1CTL =TASSEL_2+MC_1+TACLR;//选择时钟为SMCLK，UP模式
    TA1CTL  |= TAIE;//开启中断

    __enable_interrupt();//开启总中断
}
void SPWM_2Way_Set_Freq(unsigned int freq)
{
    unsigned long freq_num;
    freq_num=250000/(freq)-1;
    TA1CCR0 =freq_num;
}
/*
 * 功能：中断函数，改变SPWM中占空比寄存器的值
 * 输入：无
 * 输出：无
 * 注意：为0时双路输出，为1时单路输出
 */
/*#if 0
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TimerA1(void)
{
        TA0CCR3 =Lab1[spwm_i++];
        if(spwm_i==100)spwm_i=0;
    TA1IV=0;    //GPIO的单独中断会自动清零，可TIMER的不会，所以要软件清零；！！
}
#else
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TimerA1(void)
{
    TA0CCR3 =Lab1[spwm_i++];
    if(spwm_i==100)spwm_i=0;
    TA0CCR4 =Lab1[spwm_j++];
    if(spwm_j==100)spwm_j=0;
    TA1IV=0;    //GPIO的单独中断会自动清零，可TIMER的不会，所以要软件清零；！！
}
#endif*/