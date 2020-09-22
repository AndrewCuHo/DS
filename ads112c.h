/*
 * ads112c.h
 *
 *  Created on: 2018年8月26日
 *      Author: luoming
 */

#ifndef ADS112C_H_
#define ADS112C_H_

/**************使用范例*************/
/*
  ads112c_init(void);
  readInitXX(void);
  while(1){
      volage = goAds112c(); //volage为要读的电压值，注意不要超过最高设置的采样速度，通过配置REG_DATA修改			
  }

*/

#include <msp430f5529.h> 

#define CPU_F ((double)8000000)  //自己设置的CPU主频
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))  //延时mS

//各端口设置 ， RES可直接拉高

#define SCL_H P1OUT |= BIT3
#define SCL_L P1OUT &= ~BIT3
#define SCL_out  P1DIR|=BIT3
   
#define SDA_H P1OUT |= BIT2
#define SDA_L P1OUT &= ~BIT2
#define SDA_in  P1DIR &= ~BIT2  //SDA改成输入模式
#define SDA_out P1DIR |= BIT2  //SDA变回输出模式
#define SDA_val P1IN&BIT2    //SDA的位值
   
#define ADDR_in P1DIR &= ~BIT5 
#define ADDR_val P1IN&BIT5
   
#define RES_H P1OUT |= BIT4
#define RES_L P1OUT &= ~BIT4
#define RES_out P1DIR|=BIT4

#define FS 2.048  
   
#define GAIN2  BIT3
#define GAIN1  BIT2
#define GAIN0  BIT1

#define ADDRESS 0x80u  //A1A0接地时1119的地址
#define RESET 0x06u	      //复位命令
#define WREG1 0x40u   //  写寄存器1  
#define REG_DATA1 0x60u //A2A3差分 GAIN为0 GAIN开（外围电路配置时注意PGA的开启条件！！！）
#define WREG2 0x44u   //写寄存器2
#define REG_DATA2 0x08u //采样频率20Hz，连续转换模式
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
void readInit23(unsigned int gain);  //设置为23口差分输入，内部增益可通过gain设置为 1 8 16 64 
void readInit01(unsigned int gain,unsigned int speed);  //设置为01口差分输入，内部增益可通过gain设置为 1 4 8 16 ， 速度可通过speed设置为 20 2000
unsigned int read112c();  //读采样值（实际输出）
void ads112c_init(void);    //112c端口初始化
void ads112c_powerdown();   //112c进入低功耗休眠模式

float goAds112c(); //读采样值（转换为实际电压）



#endif /* ADS112C_H_ */