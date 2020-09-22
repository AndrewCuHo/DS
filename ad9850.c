/*
 * ad9850.c
 *
 *  Created on: 2019��7��26��
 *      Author: 09050220
 */

#include "msp430f5529.h"

#include "ad9850.h"

void ad9850_reset()
{
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);

    ad9850_w_clk_out();
    ad9850_fq_up_out();
    ad9850_rest_out() ;
    ad9850_bit_data_out();

    ad9850_w_clk_clr();
    delay_us(1);
    ad9850_fq_up_clr();

    ad9850_rest_clr();
    delay_us(1);
    ad9850_rest_set();
    delay_us(1);
    ad9850_rest_clr();

    ad9850_w_clk_clr();
    delay_us(1);
    ad9850_w_clk_set();
    delay_us(1);
    ad9850_w_clk_clr();

    ad9850_fq_up_clr();
    delay_us(1);
    ad9850_fq_up_set();
    delay_us(1);
    ad9850_fq_up_clr();
}


void ad9850_wr_serial(uint8_t w0,double frequence)
{
    uint8_t i,w;
    uint32_t y;
    double x;
    x=4294967295/125;//�ʺ�125M����
    frequence=frequence/1000000;
    frequence=frequence*x;
    y=frequence;
    //дw4����
    w=(y>>=0);
    for(i=0;i<8;i++)
    {
        if((w>>i)&0x01){
            ad9850_bit_data_set();
        }
        else{
            ad9850_bit_data_clr();
        }
        ad9850_w_clk_set();
        ad9850_w_clk_clr();
    }
    //дw3����
    w=(y>>8);
    for(i=0;i<8;i++)
    {
        if((w>>i)&0x01){
            ad9850_bit_data_set();
        }
        else{
            ad9850_bit_data_clr();
        }
        ad9850_w_clk_set();
        ad9850_w_clk_clr();
    }
    //дw2����
    w=(y>>16);
    for(i=0;i<8;i++)
    {
        if((w>>i)&0x01){
            ad9850_bit_data_set();
        }
        else{
            ad9850_bit_data_clr();
            }
        ad9850_w_clk_set();
        ad9850_w_clk_clr();

    }
    //дw1����
    w=(y>>24);
    for(i=0;i<8;i++)
    {
        if((w>>i)&0x01){
            ad9850_bit_data_set();
        }
        else{
            ad9850_bit_data_clr();
        }
        ad9850_w_clk_set();
        ad9850_w_clk_clr();
    }
    //дw0����
    w=w0;
    for(i=0;i<8;i++)
    {
        if((w>>i)&0x01){
            ad9850_bit_data_set();
        }
        else{
            ad9850_bit_data_clr();
        }
        ad9850_w_clk_set();
        ad9850_w_clk_clr();
    }
    //����ʼ��
    ad9850_fq_up_set();
    ad9850_fq_up_clr();
}
/*void main(){
    WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer
    ad9850_reset();
    ad9850_wr_serial(0x00,10000);
    while(1);


}*/

