/*
 * ads1115.c
 *
 *  Created on: 2019年7月31日
 *      Author: 09050220
 */




#include "ads1115.h"
void delay_1115(void)
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
 SDA_out;
 SCL_out;
 SCL_H;
 SDA_H;
 SDA_L;
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
        SDA_out;
	SDA_L;
	SCL_H;
	SDA_H;
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
  delay_1115();
  while((SDA_val)&&(i<250)) {
      
      i++;
  }
  SDA_out;
  SCL_L;
  delay_1115();
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
 delay_1115();
 SCL_H;
 delay_1115();
 SCL_L;
 delay_1115();
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
 delay_1115();
 SCL_H;
 delay_1115();
 SCL_L;
 delay_1115();
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
  SCL_H;
  SCL_L;
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
    SDA_in;
     for(i = 0;i < 8;i++)
     {
        SCL_L;
        SCL_H;
      flag = SDA_val;
      rdata <<= 1;
      if(flag)
          rdata |= 0x01;
       SDA_out;
    SCL_L;
    SDA_L;
    SCL_H;
    SCL_L;
    SDA_H;
     }
return rdata;
}

/*******************************************
函数名称read1115
功    能  读取转换寄存器的值
参    数无
返回值  读取的数据
********************************************/
unsigned int read1115()

{

  unsigned char result_l,result_h;
  unsigned int result;
  
  SCL_H;
  start();
  write1byte(0x91);
  ack();
  result_h=read1byte();
  result_l=read1byte();
  stop();
  result=result_h*256+result_l;
  return result;
}

void ads1115_init(void)
{
      SCL_H;
      start();
      write1byte(ADSTART);
      delay_1115();
      write1byte(Control_Regist);
      delay_1115();
      write1byte(Control_Regist_MSB);
      delay_1115();
      write1byte(Control_Regist_LSB);
      delay_1115();
      stop();
      
      SDA_out;
      SCL_H;
      start();
      write1byte(ADSTART);
      delay_1115();
      write1byte(Point_Regist);
      stop();
}

unsigned int MiddleValueFilter(void)
{
	unsigned char i, j, k;
	unsigned int Temp;
        unsigned int mj=99;
	unsigned int ArrDataBuffer[99];
	
	for (i=0; i<mj; i++)
	{
		ArrDataBuffer[i] = read1115();
                delay_ms(1);
	}
	
	for (j=0; j<mj-1; j++)
	{
		for (k=0; k<mj-j-1; k++)
		{
			if (ArrDataBuffer[k] > ArrDataBuffer[k+1])
			{
				Temp = ArrDataBuffer[k];
				ArrDataBuffer[k] = ArrDataBuffer[k+1];
				ArrDataBuffer[k+1] = Temp;
			}	
		}
	}
	
	return ArrDataBuffer[(mj-1)/2];
}

float goAds1115(){
  unsigned int temp;
  float Voltage;
  temp = MiddleValueFilter();
   if(temp>=0x8000)
   {
    temp=0xFFFF-temp;
    Voltage=(-1.0)*((temp*FS/0x8000));
   } else
   Voltage=(1.0)*((temp*FS/32768));
   return Voltage;
}
