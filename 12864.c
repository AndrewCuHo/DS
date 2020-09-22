#include <MSP430F5529.h>
#include "LCD12864.h"


//LCD12864�˿ڶ���
#define LCD12864_CS_HIGH     P4OUT|=BIT1//Ƭѡ�ź�
#define LCD12864_CS_LOW      P4OUT&=~BIT1
#define LCD12864_SID_HIGH    P4OUT|=BIT2//�����ź�
#define LCD12864_SID_LOW     P4OUT&=~BIT2
#define LCD12864_SCLK_HIGH   P6OUT|=BIT5//ʱ���ź�
#define LCD12864_SCLK_LOW    P6OUT&=~BIT5
//#define LCD12864_RST   //��λ�ź�
/********************************************************************
* ���� : IO_Init();
* ���� : ��ʼ��io��
* ���� : z
* ��� : ��
***********************************************************************/
void IO_Init()
{
	P4DIR|=BIT2+BIT1;
	P6DIR|=BIT5;
}
/********************************************************************
* ���� : LCD12864_Delay()
* ���� : ��ʱ
* ���� : z
* ��� : ��
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
* ���� : LCD12864_sendbyte
* ���� : ����Һ���Ĵ���ͨ��Э�飬��������
* ���� : zdata
* ��� : ��
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
* ���� : LCD12864_write_com()
* ���� : д����ָ������ֽ�д��
* ���� : com
* ��� : ��
***********************************************************************/
void  LCD12864_WriteCom(uchar com)
{
	  LCD12864_CS_HIGH;//��Ƭѡ���ߵ�ƽ��Ч
	  LCD12864_SendByte(0xf8); //�����һ�ֽ�  ����ʱ��ȷ����  RS RW 0 0
	  LCD12864_SendByte(com & 0xf0);	 //�ڶ��ֽ�
	  LCD12864_SendByte((com << 4) & 0xf0);//�����ֽ�
}

/********************************************************************
* ���� : LCD12864_write_date����
* ���� : д����ָ��
* ���� : date
* ��� : ��
***********************************************************************/
void LCD12864_WriteDate(uchar date)
{
	LCD12864_CS_HIGH; //��Ƭѡ
	LCD12864_SendByte(0xfa);//��һ�ֽ�     RS RW  1 0
    LCD12864_SendByte(date & 0xf0);	 //�ڶ��ֽ�
	LCD12864_SendByte((date << 4) & 0xf0);//�����ֽ�
}





/********************************************************************
* ���� : LCD12864_init()
* ���� : 12864��ʼ������
* ���� : com
* ��� : ��
***********************************************************************/
void LCD12864_Init()
{
  	 //LCD12864_RST = 0;
	 LCD12864_Delay(10);
	 //LCD12864_RST = 1;
	 LCD12864_Delay(10);
	 //LCD12864_WriteCom(0x34);//����ָ����� ,��ͼ����ʾ
	 LCD12864_WriteCom(0x30);//����ָ�����, ��ͼ����ʾ
         LCD12864_WriteCom(0x30);
	 LCD12864_WriteCom(0x0C);//����ʾ������ʾ�α���α�λ��
	 LCD12864_WriteCom(0x01);//����
	 LCD12864_WriteCom(0x06);
	 LCD12864_Delay(10);

}
void init_picture()//��ʾͼƬ�ĳ�ʼ����������ʼ����ʹ�ã�������ʾ���ֵĻ�Ӧ���ֳ�ʼ��

{

   LCD12864_WriteCom(0x36);//дָ���������ָ�����ͼG=1��
   LCD12864_Delay(10);


}
void show_Pic(uchar *address)//��ʾͼƬ����

{          //address����ָ�������ָ�룬�÷���show_Pic��XY������XYΪ������

   uchar i,j;
   for(i=0;i<32;i++)     //�ϰ�����32��������д��
   {
       LCD12864_WriteCom(0x80+i);//���ʹ�ֱ��ַ
       LCD12864_WriteCom(0x80);  //����ˮƽ��ַ��ˮƽ��ַ���Լ�1
       for(j=0;j<16;j++)//ÿ��128���㣬����һ��Ҫ16����λ16��������Ҳ����8λ��������������ȫ������
       {
          LCD12864_WriteDate(*address);   
          address++;
       }
   }
   for(i=0;i<32;i++)    //�°�����32�Ų���ԭ����ϰ���һ��
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
* ���� :LCD_clean_scans()
* ���� : ����
* ���� : ��
* ��� : ��
***********************************************************************/
void LCD12864_CleanScans()
{
 	 LCD12864_WriteCom(0x01);//����
}
/********************************************************************
* ���� :  LCD12864_pos()
* ���� : �趨��ʾλ��
* ���� :  x,y
* ��� : ��
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
	LCD12864_WriteCom(pos);//��ʾ��ַ
}
/********************************************************************
* ���� : LCD12864_dishz()
* ���� : ��ʾ�ַ���
* ���� : *s
* ��� : ��
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