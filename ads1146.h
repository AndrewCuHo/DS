#ifndef _ADS1146_H_
#define _ADS1146_H_


#include <msp430f5529.h> 

#define CPU_F ((double)8000000)
#define delay_us(x) __delay_cycles((long)(8*(double)x))

#define      ADS1146_CS         BIT0
#define      ADS1146_CLK        BIT1
#define      ADS1146_IN         BIT2
#define      ADS1146_OUT        BIT3
#define      ADS1146_DRDY       BIT4
#define      ADS1146_START      BIT5
#define      ADS1146_RESET      BIT6

 
#define      ADS1146_Port_OUT   P6OUT
#define      ADS1146_Port_DIR   P6DIR
#define      ADS1146_Port_IN    P6IN
 
#define      ADS1146_CS_OUT     (ADS1146_Port_DIR|=ADS1146_CS)
#define      SET_ADS1146_CS     (ADS1146_Port_OUT|=ADS1146_CS)
#define      CLR_ADS1146_CS     (ADS1146_Port_OUT&=~ADS1146_CS)
 
#define      ADS1146_CLK_OUT    (ADS1146_Port_DIR|=ADS1146_CLK)
#define      SET_ADS1146_CLK    (ADS1146_Port_OUT|=ADS1146_CLK)
#define      CLR_ADS1146_CLK    (ADS1146_Port_OUT&=~ADS1146_CLK)
 
#define      ADS1146_OUT_IN     (ADS1146_Port_DIR&=~ADS1146_OUT)
#define      ADS1146_OUT_Val    (ADS1146_Port_IN&ADS1146_OUT)
 
#define      ADS1146_IN_OUT     (ADS1146_Port_DIR|=ADS1146_IN)
#define      SET_ADS1146_IN     (ADS1146_Port_OUT|=ADS1146_IN)
#define      CLR_ADS1146_IN     (ADS1146_Port_OUT&=~ADS1146_IN)

#define      ADS1146_DRDY_IN     (ADS1146_Port_DIR&=~ADS1146_DRDY)
#define      ADS1146_DRDY_Val    (ADS1146_Port_IN&ADS1146_DRDY)

#define      ADS1146_START_OUT     (ADS1146_Port_DIR|=ADS1146_START)
#define      SET_ADS1146_START     (ADS1146_Port_OUT|=ADS1146_START)
#define      CLR_ADS1146_START     (ADS1146_Port_OUT&=~ADS1146_START)

#define      ADS1146_RESET_OUT     (ADS1146_Port_DIR|=ADS1146_RESET)
#define      SET_ADS1146_RESET     (ADS1146_Port_OUT|=ADS1146_RESET)
#define      CLR_ADS1146_RESET    (ADS1146_Port_OUT&=~ADS1146_RESET)

#define      WREGH    0x42u   // дREGH
#define      WREGL    0x01u   //дREGL
#define      MUX1    0x02u   //ʹ���ڲ�ʱ�ӣ�normalģʽ
#define      SYS0    0x00u //PGAΪ1 ����������5sps
#define      RDATAC    0x14u //���Ĵ���
#define      RDATA    0x12u  //������ֵ
#define      FS     1.87    //����Ϊ�ⲿ�ο���ѹ
#define      RESET  0x06u // ��λ
#define      SDATAC 0x16u 
#define      SYNC   0x04u


extern void ADS1146_init(void);
extern unsigned char ADS1146_Read(unsigned char data);  
extern void ADS1146_Voltage_Init();
extern float ADS1146_Get_Voltage(void);




#endif