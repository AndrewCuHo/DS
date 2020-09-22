/*
 * ads112c.c
 *
 *  Created on: 2018��8��26��
 *      Author: 87404
 */




#include "ads112c.h"
void delay_112c(void)
{
  
        _NOP();
}
/*******************************************
�������ƪ�start
��    �ܪ����IIC����ʼ��������
��    ������
����ֵ  ����
********************************************/
void start(void)
{
 SCL_H;
 SDA_H;
 delay_112c();
 SDA_L;
 delay_112c();
 SCL_L;
}
/*******************************************
�������ƪ�stop
��    �ܪ����IIC����ֹ��������
��    ������
����ֵ  ����
********************************************/
void stop(void)
{
 SDA_L;
 delay_112c();
 SCL_H;;
 delay_112c();
}

/*******************************************
�������ƪ�mack
��    �ܪ����IIC������Ӧ�����
��    ������
����ֵ  ����
********************************************/

void mack(void)
{
 SDA_L;
     _NOP();     _NOP();
 SCL_H;
 delay_112c();
 SCL_L;
     _NOP();    _NOP();
 SDA_H;
 delay_112c();
}
/*******************************************
�������ƪ�mnack
��    �ܪ����IIC��������Ӧ�����
��    ������
����ֵ  ����
********************************************/
void mnack(void)
{
 SDA_H;
     _NOP();     _NOP();
 SCL_H;
 delay_112c();
 SCL_L;
     _NOP();     _NOP();
 SDA_L;
 delay_112c();
}
/**********���Ӧ���źź���******************/
/*�������ֵΪ1��֤����Ӧ���źŪ���֮û��*/ /*******************************************
�������ƪ�check
��    �ܪ����ӻ���Ӧ�����
��    ������
����ֵ  ���ӻ��Ƿ���Ӧ��1--�Ъ�0--��
********************************************/
void ack()
{
  unsigned char i;
  i=0;
  SDA_in;
  SCL_H;
  delay_112c();
  while((SDA_val)&&(i<250)) {
      
      i++;
  }
  SDA_out;
  SCL_L;
  delay_112c();
}

/*******************************************
�������ƪ�write1
��    �ܪ���IIC���߷���һ��1
��    ������
����ֵ  ����
********************************************/
void write1(void)
{
 SDA_H;
 delay_112c();
 SCL_H;
 delay_112c();
 SCL_L;
 delay_112c();
}

/*******************************************
�������ƪ�write0
��    �ܪ���IIC���߷���һ��0
��    ������
����ֵ  ����
********************************************/
void write0(void)
{
 SDA_L;
 delay_112c();
 SCL_H;
 delay_112c();
 SCL_L;
 delay_112c();
}


/*******************************************
�������ƪ�write1byte
��    �ܪ���IIC���߷���һ���ֽڵ�����
��    ����wdata--���͵�����
����ֵ  ����
********************************************/
void write1byte(unsigned char wdata)
{
 unsigned char i;
 for(i = 8;i > 0;i--)
 {
  if(wdata & 0x80) write1();
  else        write0();
  wdata <<= 1;
 }
 SDA_H;
     _NOP();
}
/*******************************************
�������ƪ�read1byte
��    �ܪ���IIC���߶�ȡһ���ֽ�
��    ������
����ֵ  ����ȡ������
********************************************/
unsigned char read1byte(void)
{
 unsigned char  rdata = 0x00,i;
    unsigned char flag;
     for(i = 0;i < 8;i++)
     {
      SDA_H;
      SCL_H;
      SDA_in;
      flag = SDA_val;
      rdata <<= 1;
      if(flag)
          rdata |= 0x01;
       SDA_out;
        SCL_L;
     }
return rdata;
}

void readInit23(unsigned int gain)  
{
  unsigned char real;
  if(gain==1){
    real = REG_DATA1;
  }else if(gain==8){
    real = REG_DATA1|(GAIN1+GAIN0);
  }else if(gain==16){
    real = REG_DATA1|GAIN2;
  }else if(gain==64){
    real = REG_DATA1|(GAIN2+GAIN1);
  }
  start();
  write1byte(ADDRESS);
  ack();
  write1byte(RESET);
  ack();
  stop();
  delay_ms(5);
  start();
  write1byte(ADDRESS);
  ack();
   write1byte(WREG1);
  ack();
   write1byte(real);
  ack();
  write1byte(WREG2);
 ack();
  write1byte(REG_DATA2);
 ack();
  stop();
  delay_ms(5);
  start();
  write1byte(ADDRESS);
  ack();
  write1byte(AD_START);
  ack();
  stop();
}

void readInit01(unsigned int gain,unsigned int speed)   
{
  unsigned char real,s;
  if(gain==1){
    real = REG_DATA01;
  }else if(gain==4){
    real = REG_DATA01|(GAIN1);
  }else if(gain==8){
    real = REG_DATA01|(GAIN1+GAIN0);
  }else if(gain==16){
    real = REG_DATA01|(GAIN2);
  }
  if(speed==20){
    s = REG_DATA2;
  }if(speed==2000){
    s = REG_DATA02;
  }
  start();
  write1byte(ADDRESS);
  ack();
  write1byte(RESET);
  ack();
  stop();
  delay_ms(5);
  start();
  write1byte(ADDRESS);
  ack();
   write1byte(WREG1);
  ack();
   write1byte(real);
  ack();
  write1byte(WREG2);
 ack();
  write1byte(s);
 ack();
  stop();
  delay_ms(5);
  start();
  write1byte(ADDRESS);
  ack();
  write1byte(AD_START);
  ack();
  stop();
}


unsigned int read112c()

{

  unsigned char result_l,result_h;
  unsigned int result,i=0;

  while((ADDR_val)&&(i<250)) {
        i++;
    }

  start();
   write1byte(ADDRESS);
  ack();
   write1byte(RDATA);
  ack();
 /* stop();
  delay_ms(5);*/
  start();
  write1byte(ADDRESS+1);
  ack();
  result_h=read1byte();
  mack();
  result_l=read1byte();
  mnack();
  stop();
  result=result_h*256+result_l;
  return result;
}

void ads112c_init(void)
{
      SCL_out;
      SDA_out;
      RES_out;
      ADDR_in;
      RES_L;
      SCL_H;
      SDA_H;
      RES_H;
      stop();
}
float goAds112c(){
  unsigned int temp;
  float Voltage;
  temp = read112c();
   if(temp>=0x8000)
   {
    temp=0xFFFF-temp;
    Voltage=(-1.0)*((temp*FS/0x8000));
   } else
   Voltage=(1.0)*((temp*FS/32768));
   return Voltage;
}
 
void ads112c_powerdown(){
   start();
  write1byte(ADDRESS);
  ack();
  write1byte(POWERDOWN);
  ack();
  stop();
}
