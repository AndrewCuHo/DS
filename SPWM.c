/*----------------------------------------------------------------------------------------------
 * ���ܣ�������·SPWM��
 * ���룺��
 * �����P1.4
 * ע�⣺��ʱ��ҲΪTA1.1;�ز�Ƶ��Ϊ126.26K����Ĭ������Ƶ��Ϊ100HZ������δ֪
 */
#include <MSP430.h> 
#include "SPWM.h"
void SPWM_1Way_Init(void)
{
    P1SEL |=BIT4;
    P1DIR |=BIT4;
    //P1DS |=BIT4; //ȫ������
    P1OUT &=~BIT4;
    spwm_i=0;
    TA0CCR0 =9;//�ز�126.26KHZ
    TA0CCR3 =Lab1[spwm_i];
    TA0CCTL3 =OUTMOD_7;
    TA0CTL =TASSEL_2+MC_1+TACLR;//ѡ��ʱ��ΪSMCLK��UPģʽ

    P2SEL |=BIT0;
    P2DIR |=BIT0;
    P2OUT &=~BIT0;
    TA1CCR0 =2499;//25000000/(100*100)=2500:100Hz��100���㣺10KHZ(ʱ�䲻̫׼������Щ����)
    TA1CTL =TASSEL_2+MC_1+TACLR;//ѡ��ʱ��ΪSMCLK��UPģʽ
    TA1CTL  |= TAIE;//�����ж�

    __enable_interrupt();//�������ж�
}
void SPWM_1Way_Set_Freq(unsigned int freq)
{
    unsigned long freq_num;
    freq_num=2500000/(freq)-1;
    TA1CCR0 =freq_num;
}
/*
 * ���ܣ������·SPWM������λ�ɵ�
 * ���룺��
 * �����P1.4,P1.5
 * ע�⣺��ʱ��ҲΪTA1.1;�ز�Ƶ��Ϊ126.26K����Ĭ������Ƶ��Ϊ100HZ������δ֪
 */
void SPWM_2Way_Init(void)
{
    P1SEL |=BIT4+BIT5;
    P1DIR |=BIT4+BIT5;
    //P1DS |=BIT4+BIT5; //ȫ������
    P1OUT &=~BIT4+BIT5;
    spwm_i=0;
    spwm_j=0;//������λ
    TA0CCR0 =198;//�ز�126.26KHZ
    TA0CCR3 =Lab1[spwm_i];
    TA0CCR4 =Lab1[spwm_j];
    TA0CCTL3 =OUTMOD_7;
    TA0CCTL4 =OUTMOD_7;
    TA0CTL =TASSEL_2+MC_1+TACLR;//ѡ��ʱ��ΪSMCLK��UPģʽ

    P2SEL |=BIT0;
    P2DIR |=BIT0;
    P2OUT &=~BIT0;
    TA1CCR0 =2499;//25000000/(100*100)=2500:100Hz��100���㣺10KHZ
    TA1CTL =TASSEL_2+MC_1+TACLR;//ѡ��ʱ��ΪSMCLK��UPģʽ
    TA1CTL  |= TAIE;//�����ж�

    __enable_interrupt();//�������ж�
}
void SPWM_2Way_Set_Freq(unsigned int freq)
{
    unsigned long freq_num;
    freq_num=250000/(freq)-1;
    TA1CCR0 =freq_num;
}
/*
 * ���ܣ��жϺ������ı�SPWM��ռ�ձȼĴ�����ֵ
 * ���룺��
 * �������
 * ע�⣺Ϊ0ʱ˫·�����Ϊ1ʱ��·���
 */
/*#if 0
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TimerA1(void)
{
        TA0CCR3 =Lab1[spwm_i++];
        if(spwm_i==100)spwm_i=0;
    TA1IV=0;    //GPIO�ĵ����жϻ��Զ����㣬��TIMER�Ĳ��ᣬ����Ҫ������㣻����
}
#else
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TimerA1(void)
{
    TA0CCR3 =Lab1[spwm_i++];
    if(spwm_i==100)spwm_i=0;
    TA0CCR4 =Lab1[spwm_j++];
    if(spwm_j==100)spwm_j=0;
    TA1IV=0;    //GPIO�ĵ����жϻ��Զ����㣬��TIMER�Ĳ��ᣬ����Ҫ������㣻����
}
#endif*/