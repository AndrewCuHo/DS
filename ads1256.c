/*
 * ads1256.c
 *
 *  Created on: 2019年7月27日
 *      Author: 87404
 */


#include "ads1256.h"

extern uint32_t FSC;
extern int32_t OFC;
extern uint32_t adValue[1024];



void ADS1256IOInit(){
    ADS1256_Write_SCLK_Out;
    ADS1256_Write_DIN_Out;
    ADS1256_Dout_In;
    ADS1256_Write_CS_Out;
    ADS1256_Write_SYNC_Out;
    ADS1256_DRDY_In;
}


void ADS1256_write_bit(uint8_t temp)
{
    uint8_t i;
    for(i=0;i<8;i++)
    {
        ADS1256_Write_SCLK_H;
        if(temp&0x80)
            ADS1256_Write_DIN_H;
        else
            ADS1256_Write_DIN_L;
        temp=temp<<1;
        ADS1256_Write_SCLK_L;
        delay_us(1);
    }
    delay_us(5);
}


uint8_t ADS1256_read_bit(void)
{
    uint8_t i;
    uint8_t data = 0;
    for(i=0;i<8;i++)
    {
        ADS1256_Write_SCLK_H;
        ADS1256_Write_SCLK_L;
        data <<= 1;
        if(ADS1256_Read_DOUT)
             data += 1;
    }
    return data;

}

void ADS1256_write_reg(uint8_t addr, uint8_t data){
    uint8_t temp = 0;
    temp = 0x50 + (addr&0x0F);
    ADS1256_write_bit(temp);
    ADS1256_write_bit(0x00);  //写一个寄存器
    ADS1256_write_bit(data);
}

uint8_t ADS1256_read_reg(uint8_t addr){
    uint8_t temp = 0;
    temp = 0x10 + (addr&0x0F);
    ADS1256_write_bit(temp);
    ADS1256_write_bit(0x00);  //读一个寄存器
    temp = ADS1256_read_bit();
    return temp;
}

uint8_t ADS1256_Init(uint8_t channel,uint16_t PGAGain,uint16_t tranSpeed){

    //channel is 0xPN
    //PGAGain is 1,2,4,8,16,32 or 64
    //transSpeed is 2(turely 2.5),5,10,15,25,30,50,60,100,500,1000,2000,3750,7500,15000 or 30000

    uint8_t ReturnData = 0;
    uint8_t ADS1256_reg_Init[5]={
        0x00,  //状态寄存器初始化值
        0x01,  //模拟多路选择器初始化值
        0x00,  //AD控制寄存器初始化值
        0x03,  //数据速度寄存器初始化值
        0x00, //I/O控制寄存器初始化值
     };

    ADS1256_reg_Init[1] = channel;

    switch(PGAGain){
        case     1:    ADS1256_reg_Init[2] = 0x00;break;
        case     2:    ADS1256_reg_Init[2] = 0x01;break;
        case     4:    ADS1256_reg_Init[2] = 0x02;break;
        case     8:    ADS1256_reg_Init[2] = 0x03;break;
        case    16:    ADS1256_reg_Init[2] = 0x04;break;
        case    32:    ADS1256_reg_Init[2] = 0x05;break;
        case    64:    ADS1256_reg_Init[2] = 0x06;break;
        default   :    ADS1256_reg_Init[2] = 0x00;PGAGain = 1;break;
    }
    switch(tranSpeed){
        case     2:    ADS1256_reg_Init[3] = 0x03;break;
        case     5:    ADS1256_reg_Init[3] = 0x13;break;
        case    10:    ADS1256_reg_Init[3] = 0x23;break;
        case    15:    ADS1256_reg_Init[3] = 0x33;break;
        case    25:    ADS1256_reg_Init[3] = 0x43;break;
        case    30:    ADS1256_reg_Init[3] = 0x53;break;
        case    50:    ADS1256_reg_Init[3] = 0x63;break;
        case    60:    ADS1256_reg_Init[3] = 0x72;break;
        case   100:    ADS1256_reg_Init[3] = 0x82;break;
        case   500:    ADS1256_reg_Init[3] = 0x92;break;
        case  1000:    ADS1256_reg_Init[3] = 0xA1;break;
        case  2000:    ADS1256_reg_Init[3] = 0xB0;break;
        case  3750:    ADS1256_reg_Init[3] = 0xC0;break;
        case  7500:    ADS1256_reg_Init[3] = 0xD0;break;
        case 15000:    ADS1256_reg_Init[3] = 0xE0;break;
        case 30000:    ADS1256_reg_Init[3] = 0xF0;break;
        default   :    ADS1256_reg_Init[3] = 0x03;break;
    }



     ADS1256IOInit();
     ADS1256_Write_CS_H;
     ADS1256_Write_SYNC_H;
     ADS1256_Write_SCLK_L;
     //ADS1256_Write_RST_L;
     //SysCtlDelay(SysCtlClockGet() /120);
     //ADS1256_Write_RST_H;
     delay_ms(1);
     ADS1256_Write_CS_L;
     delay_ms(1);
     ADS1256_write_bit(0xFE); //reset
     ADS1256_write_reg(0x00,ADS1256_reg_Init[0]);//状态寄存器初始化


     ADS1256_write_reg(0x01,ADS1256_reg_Init[1]);//模拟多路选择器初始化
     delay_ms(1);
     ADS1256_write_reg(0x02,ADS1256_reg_Init[2]);//AD控制寄存器初始化
     delay_ms(1);
     ADS1256_write_reg(0x03,ADS1256_reg_Init[3]);//数据速度寄存器初始化
     delay_ms(1);
     ADS1256_write_reg(0x04,ADS1256_reg_Init[4]);//I/O控制寄存器初始化
     delay_ms(1);
     if(ADS1256_reg_Init[1] != ADS1256_read_reg(0x01))  ReturnData = 1;
     delay_ms(1);
     if(ADS1256_reg_Init[2] != ADS1256_read_reg(0x02))  ReturnData = 1;
     delay_ms(1);
     if(ADS1256_reg_Init[3] != ADS1256_read_reg(0x03))  ReturnData = 1;
     delay_ms(1);
     if(ADS1256_reg_Init[4] != ADS1256_read_reg(0x04))  ReturnData = 1;
     delay_ms(1);

     ADS1256_write_bit(0xF0);   //执行自校准

     while(ADS1256_Read_DRDY);

     getcalibration();     //读取自校准参数

     ADS1256_write_bit(0xFC);  //DRDY
     ADS1256_write_bit(0x00);   //wakeUp

     return(ReturnData);
}

uint32_t ADS1256_Read_a_Data(void)
{
    uint32_t Data = 0,Data1 = 0,Data2 = 0,Data3 = 0;
    while(ADS1256_Read_DRDY);
    ADS1256_write_bit(0x01);
   // SysCtlDelay(SysCtlClockGet() /120);
    Data1 = ADS1256_read_bit();
    Data2 = ADS1256_read_bit();
    Data3 = ADS1256_read_bit();
    Data = (Data1<<16) | (Data2<<8) | Data3;
    return (Data);
}

void getcalibration(){
    uint32_t Data1 = 0,Data2 = 0,Data3 = 0;
    ADS1256_write_bit(0x15);
    ADS1256_write_bit(0x05);  //读六个寄存器
    Data1 = ADS1256_read_bit();
    Data2 = ADS1256_read_bit();
    Data3 = ADS1256_read_bit();
    OFC = (Data3<<16) | (Data2<<8) | Data1;
    Data1 = ADS1256_read_bit();
    Data2 = ADS1256_read_bit();
    Data3 = ADS1256_read_bit();
    FSC = (Data3<<16) | (Data2<<8) | Data1;
    if(OFC>0x800000){
        OFC -= 0xFFFFFF;
    }
}

float computeVoltage(uint32_t Data,uint16_t PGAGain,uint16_t tranSpeed){
    //PGAGain is 1,2,4,8,16,32 or 64
    float temp = 0,beta;
    uint32_t alpha = 0;
       switch(tranSpeed){
           case     2:    alpha = 0x5DC000; beta = 2.7304 ;break;
           case     5:    alpha = 0x5DC000; beta = 2.7304 ;break;
           case    10:    alpha = 0x5DC000; beta = 2.7304 ;break;
           case    15:    alpha = 0x3E8000; beta = 1.8202 ;break;
           case    25:    alpha = 0x4B0000; beta = 2.1843 ;break;
           case    30:    alpha = 0x3E8000; beta = 1.8202 ;break;
           case    50:    alpha = 0x4B0000; beta = 2.1843 ;break;
           case    60:    alpha = 0x3E8000; beta = 1.8202 ;break;
           case   100:    alpha = 0x4B0000; beta = 2.1843 ;break;
           case   500:    alpha = 0x3C0000; beta = 1.7474 ;break;
           case  1000:    alpha = 0x3C0000; beta = 1.7474 ;break;
           case  2000:    alpha = 0x3C0000; beta = 1.7474 ;break;
           case  3750:    alpha = 0x400000; beta = 1.8639 ;break;
           case  7500:    alpha = 0x400000; beta = 1.8639 ;break;
           case 15000:    alpha = 0x400000; beta = 1.8639 ;break;
           case 30000:    alpha = 0x400000; beta = 1.8639 ;break;
           default   :    alpha = 0x400000; beta = 1.8639 ;break;
       }
    if(Data<0x800000) {
       // temp = Data * 2 * 2.49833 / 0x7FFFFF;
        temp = (Data /((float)FSC) /beta + ((float)OFC) / alpha) * 2.0 * 2.51341288/PGAGain;
        temp = 0.998708 * temp + 0.018135;
        
    }else{
        Data=0xFFFFFF-Data;
      //  temp = -(Data * 2 * 2.49833 / 0x7FFFFF);
        temp =  - (Data /((float)FSC) /beta + ((float)OFC) / alpha) * 2.0 * 2.51341288/PGAGain;
        temp = 0.998708 * temp - 0.018135;
    }
    return temp;
}

void adGet1000(uint8_t channel,uint16_t PGAGain,uint16_t tranSpeed){
    uint32_t Data = 0;
    //channel is 0xPN
    //PGAGain is 1,2,4,8,16,32 or 64
    //transSpeed is 2(turely 2.5),5,10,15,25,30,50,60,100,500,1000,2000,3750,7500,15000 or 30000

    int i,j;
    while(ADS1256_Init(channel,PGAGain,tranSpeed));
    while(ADS1256_Read_DRDY);
    ADS1256_write_bit(0x03);
    for(i = 0; i < 1000 ; i++){
        while(ADS1256_Read_DRDY);
        Data = 0;
        for(j=0;j<24;j++)
            {
                ADS1256_Write_SCLK_H;
                ADS1256_Write_SCLK_L;
                Data <<= 1;
                if(ADS1256_Read_DOUT)
                     Data += 1;
            }
        adValue[i] = Data;
        /*if(i%2 == 0){
            P2OUT |= BIT0;
        }else{
            P2OUT &= ~BIT0;
        }*/
       // delay_us(15);
    }
    while(ADS1256_Read_DRDY);
    ADS1256_write_bit(0x0F);
}

