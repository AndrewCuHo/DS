#include "ads1146.h"

void ADS1146_init(void)
{
 ADS1146_CS_OUT;
 ADS1146_CLK_OUT;
 ADS1146_IN_OUT;
 ADS1146_OUT_IN;
 ADS1146_DRDY_IN ;
 ADS1146_START_OUT  ;
 ADS1146_RESET_OUT;
 
 CLR_ADS1146_RESET;
 _NOP();
 SET_ADS1146_CS;
 _NOP();
 CLR_ADS1146_CLK;
 _NOP();
 CLR_ADS1146_IN;
 _NOP();
 SET_ADS1146_START ;
 _NOP();
 SET_ADS1146_RESET;
 _NOP();
}


unsigned char ADS1146_Read(unsigned char data)   //SPI为全双工通信方式
{
 unsigned char i,temp,Din;
  temp=data;
  CLR_ADS1146_CS;
  delay_us(1);
  for(i=0;i<8;i++)
  {
   Din = Din<<1;
   if(0x80&temp)
    SET_ADS1146_IN;
   else
    CLR_ADS1146_IN;
    delay_us(1);
    SET_ADS1146_CLK;
   delay_us(1);
   if(ADS1146_OUT_Val)
    Din |= 0x01;
    delay_us(1);
    CLR_ADS1146_CLK;
    _NOP();
    delay_us(1);
    temp = (temp<<1);
  }
  SET_ADS1146_CS;
  delay_us(50);
  return Din;
}       
void ADS1146_Voltage_Init(){
  unsigned int i=0;
  ADS1146_Read((unsigned char)(RESET));
  delay_us(1000);
   ADS1146_Read((unsigned char)(SDATAC));
   
   while((ADS1146_DRDY_Val)&&(i<1000)) 
   {i++;delay_us(1);}
  ADS1146_Read((unsigned char)(WREGH));
  ADS1146_Read((unsigned char)(WREGL));
  ADS1146_Read((unsigned char)(MUX1));
  ADS1146_Read((unsigned char)(SYS0));
  ADS1146_Read((unsigned char)(SYNC));
}

float ADS1146_Get_Voltage(void)
{
 unsigned int i=0;
 unsigned char Data_REG_H,Data_REG_L;
 unsigned int Data_REG;
 float ADS1146_Voltage;
 while((ADS1146_DRDY_Val)&&(i<1000)) i++;
 ADS1146_Read((unsigned char)(RDATA));
  while((ADS1146_DRDY_Val)&&(i<1000)) 
   {i++;delay_us(1);}
 Data_REG_H=ADS1146_Read(0x00);
 Data_REG_L=ADS1146_Read(0x00);
  Data_REG=(Data_REG_H<<8)+Data_REG_L;
 if(Data_REG>=0x8000) {
    Data_REG=0xFFFF-Data_REG;//把0xFFFF改成0x10000
    ADS1146_Voltage=(-1.0)*((Data_REG*FS/0x8000));
   }else   ADS1146_Voltage=(1.0)*((Data_REG*FS/32768));
 return ADS1146_Voltage;
    
}
 
 