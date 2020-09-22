/*
 * ads112c.h
 *
 *  Created on: 2018��8��26��
 *      Author: luoming
 */

#ifndef ADS112C_H_
#define ADS112C_H_

/**************ʹ�÷���*************/
/*
  ads112c_init(void);
  readInitXX(void);
  while(1){
      volage = goAds112c(); //volageΪҪ���ĵ�ѹֵ��ע�ⲻҪ����������õĲ����ٶȣ�ͨ������REG_DATA�޸�			
  }

*/

#include <msp430f5529.h> 

#define CPU_F ((double)8000000)  //�Լ����õ�CPU��Ƶ
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))  //��ʱmS

//���˿����� �� RES��ֱ������

#define SCL_H P1OUT |= BIT3
#define SCL_L P1OUT &= ~BIT3
#define SCL_out  P1DIR|=BIT3
   
#define SDA_H P1OUT |= BIT2
#define SDA_L P1OUT &= ~BIT2
#define SDA_in  P1DIR &= ~BIT2  //SDA�ĳ�����ģʽ
#define SDA_out P1DIR |= BIT2  //SDA������ģʽ
#define SDA_val P1IN&BIT2    //SDA��λֵ
   
#define ADDR_in P1DIR &= ~BIT5 
#define ADDR_val P1IN&BIT5
   
#define RES_H P1OUT |= BIT4
#define RES_L P1OUT &= ~BIT4
#define RES_out P1DIR|=BIT4

#define FS 2.048  
   
#define GAIN2  BIT3
#define GAIN1  BIT2
#define GAIN0  BIT1

#define ADDRESS 0x80u  //A1A0�ӵ�ʱ1119�ĵ�ַ
#define RESET 0x06u	      //��λ����
#define WREG1 0x40u   //  д�Ĵ���1  
#define REG_DATA1 0x60u //A2A3��� GAINΪ0 GAIN������Χ��·����ʱע��PGA�Ŀ���������������
#define WREG2 0x44u   //д�Ĵ���2
#define REG_DATA2 0x08u //����Ƶ��20Hz������ת��ģʽ
#define AD_START 0x08u  
#define RDATA  0x10u
#define POWERDOWN 0x02u
   
#define REG_DATA01 0x00u
#define REG_DATA02 0xD8u

   
void delay_112c(void);
void start(void);
void stop(void);
void mack(void);
void mnack(void);
void ack();
void write1(void);
void write0(void);
void write1byte(unsigned char wdata);
unsigned char read1byte(void);
void readInit23(unsigned int gain);  //����Ϊ23�ڲ�����룬�ڲ������ͨ��gain����Ϊ 1 8 16 64 
void readInit01(unsigned int gain,unsigned int speed);  //����Ϊ01�ڲ�����룬�ڲ������ͨ��gain����Ϊ 1 4 8 16 �� �ٶȿ�ͨ��speed����Ϊ 20 2000
unsigned int read112c();  //������ֵ��ʵ�������
void ads112c_init(void);    //112c�˿ڳ�ʼ��
void ads112c_powerdown();   //112c����͹�������ģʽ

float goAds112c(); //������ֵ��ת��Ϊʵ�ʵ�ѹ��



#endif /* ADS112C_H_ */