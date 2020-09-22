/*
 * ad9850.h
 *
 *  Created on: 2019Äê8ÔÂ1ÈÕ
 *      Author: 09050220
 */

#ifndef AD9850_H_
#define AD9850_H_
#include <stdint.h>
#include <stdbool.h>
#include <msp430.h>

#define CPU_F                               ((double)8000000)
#define delay_us(x)                      __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x)                      __delay_cycles((long)(CPU_F*(double)x/1000.0))


#define     ad9850_w_clk_out()              P3DIR|=BIT4;//GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE,GPIO_PIN_0)
#define     ad9850_w_clk_set()              P3OUT|=BIT4;//GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_0, GPIO_PIN_0)
#define     ad9850_w_clk_clr()              P3OUT&=~BIT4;//GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_0,0)

#define     ad9850_fq_up_out()              P6DIR|=BIT6;//GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE,GPIO_PIN_1)
#define     ad9850_fq_up_set()              P6OUT|=BIT6;//GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_1, GPIO_PIN_1)
#define     ad9850_fq_up_clr()              P6OUT&=~BIT6;//GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_1,0)

#define     ad9850_rest_out()               P4DIR|=BIT2;
#define     ad9850_rest_set()               P4OUT|=BIT2;
#define     ad9850_rest_clr()               P4OUT&=~BIT2;

#define     ad9850_bit_data_out()           P3DIR|=BIT2;
#define     ad9850_bit_data_set()           P3OUT|=BIT2;
#define     ad9850_bit_data_clr()           P3OUT&=~BIT2;


void ad9850_reset();
void ad9850_wr_serial(uint8_t w0,double frequence);



#endif /* AD9850_H_ */
