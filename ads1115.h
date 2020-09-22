/*
 * ads1115.h
 *
 *  Created on: 2019年7月31日
 *      Author: 09050220
 */

#ifndef ADS1115_H_
#define ADS1115_H_

/**************使用范例*************/
/*
  ads1115_init(void);
  readInitXX(void);
  while(1){
      volage = goAds1115(); //volage为要读的电压值，注意不要超过最高设置的采样速度，通过配置REG_DATA修改			
  }

*/

#include <msp430f5529.h> 

#define CPU_F ((double)8000000)  //自己设置的CPU主频
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))  //延时mS
#define delay_us(x) __delay_cycles((long)((CPU_F*(double)x/1000000.0)))//延时us

//各端口设置 ， RES可直接拉高

#define SCL_H P6OUT |= BIT5
#define SCL_L P6OUT &= ~BIT5
#define SCL_out  P6DIR|=BIT5
   
#define SDA_H P6OUT |= BIT6
#define SDA_L P6OUT &= ~BIT6
#define SDA_in  P6DIR &= ~BIT6  //SDA改成输入模式
#define SDA_out P6DIR |= BIT6  //SDA变回输出模式
#define SDA_val P6IN&BIT6    //SDA的位值
   
#define      OS          BITF      //    0    Unused in Continuous conversion mode(Always reads back as 0)
#define      MUX2        BITE      //    1
#define      MUX1        BITD      //    0
#define      MUX0        BITC      //    0    100 = AINP is AIN0 and AINN is GND
#define      PGA2        BITB      //    0
#define      PGA1        BITA      //    1
#define      PGA0        BIT9      //    0    010 = FS is ±2.048 V(default)
#define      MODE        BIT8      //    1    1 = Continuous conversion mode
 
#define      FS          2.048
 
#define      DR2         BIT7      //    1
#define      DR1         BIT6      //    0
#define      DR0         BIT5      //    1    100 = 128 SPS (default)
#define      CMP_MODE    BIT4      //    0    NOT USED COMPARE -- 
#define      COMPATOR    BIT3      //    0    0 = Compator resistor enabled on DOUT/DRDY pin (default)
#define      NOP2        BIT2      //    0
#define      NOP1        BIT1      //    1    01 = Valid data, update the Config register (default)
#define      NOP0        BIT0      //    1    Always reads '1'

#define ADSTART 0x90                  //开始I2C传输
#define Control_Regist 0x01	      //指向CONFIG REGISTER
#define Control_Regist_MSB (PGA1 + MODE)
#define Control_Regist_LSB (DR0 + DR2 + NOP1 + NOP0) 
#define Point_Regist 0x00

void delay_1115(void);
void start(void);
void stop(void);
void ack();
void write1(void);
void write0(void);
void write1byte(unsigned char wdata);
unsigned char read1byte(void);
unsigned int read1115();  //读采样值（实际输出）
void ads1115_init(void);    //112c端口初始化
float goAds1115(); //读采样值（转换为实际电压）
unsigned int MiddleValueFilter(void); //中值滤波


#endif /* ADS1115_H_ */