/*
 * ads1256.h
 *
 *  Created on: 2019Äê7ÔÂ27ÈÕ
 *      Author: 87404
 */

#ifndef ADS1256_H_
#define ADS1256_H_

#include <stdint.h>
#include <stdbool.h>
#include <msp430.h>


#define CPU_F                               ((double)8000000)
#define delay_us(x)                      __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x)                      __delay_cycles((long)(CPU_F*(double)x/1000.0))


#define ADS1256_Write_SCLK_Out    P6DIR|=BIT5
#define ADS1256_Write_SCLK_H   P6OUT |= BIT5
#define ADS1256_Write_SCLK_L    P6OUT &= ~BIT5

#define ADS1256_Write_DIN_Out       P6DIR|=BIT1
#define ADS1256_Write_DIN_H       P6OUT |= BIT1
#define ADS1256_Write_DIN_L       P6OUT &= ~BIT1

#define ADS1256_Dout_In               P6DIR &= ~BIT2
#define ADS1256_Read_DOUT             P6IN&BIT2

#define ADS1256_Write_CS_Out         P6DIR|=BIT4
#define ADS1256_Write_CS_H        P6OUT |= BIT4
#define ADS1256_Write_CS_L          P6OUT &= ~BIT4

#define ADS1256_Write_SYNC_Out       P7DIR|=BIT0
#define ADS1256_Write_SYNC_H      P7OUT |= BIT0
#define ADS1256_Write_SYNC_L      P7OUT &= ~BIT0

#define ADS1256_DRDY_In             P6DIR &= ~BIT3
#define ADS1256_Read_DRDY           P6IN&BIT3


void ADS1256IOInit();
void ADS1256_write_bit(uint8_t temp);
uint8_t ADS1256_read_bit(void);
void ADS1256_write_reg(uint8_t addr, uint8_t data);
uint8_t ADS1256_read_reg(uint8_t addr);
uint8_t ADS1256_Init(uint8_t channel,uint16_t PGAGain,uint16_t tranSpeed);
uint32_t ADS1256_Read_a_Data(void);
void getcalibration();
float computeVoltage(uint32_t Data,uint16_t PGAGain,uint16_t tranSpeed);
void adGet1000(uint8_t channel,uint16_t PGAGain,uint16_t tranSpeed);

#endif /* ADS1256_H_ */
