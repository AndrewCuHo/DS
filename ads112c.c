/*
 * ads112c.c
 *
 *  Created on: 2018年8月26日
 *      Author: 87404
 */




#include "ads112c.h"
void delay_112c(void)
{
  
        _NOP();
}
/*******************************************
函数名称start
功    能完成IIC的起始条件操作
参    数无
返回值  无
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
函数名称stop
功    能完成IIC的终止条件操作
参    数无
返回值  无
********************************************/
void stop(void)
{
 SDA_L;
 delay_112c();
 SCL_H;;
 delay_112c();
}

/*******************************************
函数名称mack
功    能完成IIC的主机应答操作
参    数无
返回值  无
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
函数名称mnack
功    能完成IIC的主机无应答操作
参    数无
返回值  无
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
/**********检查应答信号函数******************/
/*如果返回值为1则证明有应答信号反之没有*/ /*******************************************
函数名称check
功    能检查从机的应答操作
参    数无
返回值  从机是否有应答1--有0--无
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
函数名称write1
功    能向IIC总线发送一个1
参    数无
返回值  无
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
函数名称write0
功    能向IIC总线发送一个0
参    数无
返回值  无
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
函数名称write1byte
功    能向IIC总线发送一个字节的数据
参    数wdata--发送的数据
返回值  无
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
函数名称read1byte
功    能从IIC总线读取一个字节
参    数无
返回值  读取的数据
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
