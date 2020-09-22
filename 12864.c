#include <MSP430F5529.h>
#include "LCD12864.h"


//LCD12864端口定义
#define LCD12864_CS_HIGH     P4OUT|=BIT1//片选信号
#define LCD12864_CS_LOW      P4OUT&=~BIT1
#define LCD12864_SID_HIGH    P4OUT|=BIT2//数据信号
#define LCD12864_SID_LOW     P4OUT&=~BIT2
#define LCD12864_SCLK_HIGH   P6OUT|=BIT5//时钟信号
#define LCD12864_SCLK_LOW    P6OUT&=~BIT5
//#define LCD12864_RST   //复位信号
/********************************************************************
* 名称 : IO_Init();
* 功能 : 初始化io口
* 输入 : z
* 输出 : 无
***********************************************************************/
void IO_Init()
{
	P4DIR|=BIT2+BIT1;
	P6DIR|=BIT5;
}
/********************************************************************
* 名称 : LCD12864_Delay()
* 功能 : 延时
* 输入 : z
* 输出 : 无
***********************************************************************/
void LCD12864_Delay(uint z)
{
//	uchar i;
//	while(z --) for(i = 0;i < 120;i ++);
	uint a,b;
 	for(a=0; a<z; a++)
   		for(b=0; b<120; b++);
}
/********************************************************************
* 名称 : LCD12864_sendbyte
* 功能 : 按照液晶的串口通信协议，发送数据
* 输入 : zdata
* 输出 : 无
***********************************************************************/
void LCD12864_SendByte(uchar zdata)
{
	uchar i;
	for(i = 0;i < 8;i ++)
	{
		LCD12864_SCLK_HIGH;
		if((zdata<<i) & 0x80)
		{
			LCD12864_SID_HIGH;
		}
		else
		{
		    LCD12864_SID_LOW;
		}
		LCD12864_SCLK_LOW;
                LCD12864_Delay(10);
	}
}
/********************************************************************
* 名称 : LCD12864_write_com()
* 功能 : 写串口指令，分三字节写完
* 输入 : com
* 输出 : 无
***********************************************************************/
void  LCD12864_WriteCom(uchar com)
{
	  LCD12864_CS_HIGH;//打开片选，高电平有效
	  LCD12864_SendByte(0xf8); //送入第一字节  根据时序确定的  RS RW 0 0
	  LCD12864_SendByte(com & 0xf0);	 //第二字节
	  LCD12864_SendByte((com << 4) & 0xf0);//第三字节
}

/********************************************************************
* 名称 : LCD12864_write_date（）
* 功能 : 写串口指令
* 输入 : date
* 输出 : 无
***********************************************************************/
void LCD12864_WriteDate(uchar date)
{
	LCD12864_CS_HIGH; //打开片选
	LCD12864_SendByte(0xfa);//第一字节     RS RW  1 0
    LCD12864_SendByte(date & 0xf0);	 //第二字节
	LCD12864_SendByte((date << 4) & 0xf0);//第三字节
}





/********************************************************************
* 名称 : LCD12864_init()
* 功能 : 12864初始化函数
* 输入 : com
* 输出 : 无
***********************************************************************/
void LCD12864_Init()
{
  	 //LCD12864_RST = 0;
	 LCD12864_Delay(10);
	 //LCD12864_RST = 1;
	 LCD12864_Delay(10);
	 //LCD12864_WriteCom(0x34);//扩充指令集动作 ,绘图不显示
	 LCD12864_WriteCom(0x30);//基本指令集动作, 绘图不显示
         LCD12864_WriteCom(0x30);
	 LCD12864_WriteCom(0x0C);//开显示，不显示游标和游标位置
	 LCD12864_WriteCom(0x01);//清屏
	 LCD12864_WriteCom(0x06);
	 LCD12864_Delay(10);

}
void init_picture()//显示图片的初始化函数（初始化后使用），再显示文字的话应重现初始化

{

   LCD12864_WriteCom(0x36);//写指令函数，扩充指令集，绘图G=1打开
   LCD12864_Delay(10);


}
void show_Pic(uchar *address)//显示图片函数

{          //address是是指向数组的指针，用法：show_Pic（XY）当中XY为数组名

   uchar i,j;
   for(i=0;i<32;i++)     //上半屏的32排依次先写满
   {
       LCD12864_WriteCom(0x80+i);//先送垂直地址
       LCD12864_WriteCom(0x80);  //再送水平地址，水平地址可自加1
       for(j=0;j<16;j++)//每排128个点，所以一共要16个两位16进制数（也就是8位二进制数）才能全部控制
       {
          LCD12864_WriteDate(*address);   
          address++;
       }
   }
   for(i=0;i<32;i++)    //下半屏的32排操作原理和上半屏一样
   {
      LCD12864_WriteCom(0x80+i);
      LCD12864_WriteCom(0x88);
      for(j=0;j<16;j++)
       {
          LCD12864_WriteDate(*address);   
          address++;
       }
   }
}
/*void show_Pic_H(uchar *address){
  uchar i,j;
  for(i=0;i<64;i++){
    for(j=0;j<32;j++){
      LCD12864_WriteCom(0x80+i);
      LCD12864_WriteCom(0x80+j);
      LCD12864_WriteDate(*address); 
      address++;
    }
  }
}*/
/********************************************************************
* 名称 :LCD_clean_scans()
* 功能 : 清屏
* 输入 : 无
* 输出 : 无
***********************************************************************/
void LCD12864_CleanScans()
{
 	 LCD12864_WriteCom(0x01);//清屏
}
/********************************************************************
* 名称 :  LCD12864_pos()
* 功能 : 设定显示位置
* 输入 :  x,y
* 输出 : 无
***********************************************************************/
void LCD12864_SetPos(uchar x,uchar y)
{
	uchar pos;
	if(x == 0)
        	x = 0x80;
	else if(x == 1)
	        x = 0x90;
	else if(x == 2)
	        x = 0x88;
	else if(x == 3)
		    x = 0x98;
	pos = x + y;
	LCD12864_WriteCom(pos);//显示地址
}
/********************************************************************
* 名称 : LCD12864_dishz()
* 功能 : 显示字符串
* 输入 : *s
* 输出 : 无
***********************************************************************/
void LCD12864_DisplayString(uchar *s,uchar n)
{
	uchar  i = 0,mun=0;
	mun=n;
	for(i=0;i<mun;i++)
    {
		LCD12864_WriteDate(s[i]);

	 	LCD12864_Delay(5);
    }
}


void set_pos(uchar addr,uchar x)
{
     x&=0x07;
     LCD12864_WriteCom(addr+x);
}
void lcd_send_data(uchar x,uchar y,uchar *s)
{
     LCD12864_SetPos(x,y);
     while(*s!=0){
          LCD12864_WriteDate(*s);
          LCD12864_Delay(5);
          s++;
     }
     
}