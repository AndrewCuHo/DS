#include <msp430f5529.h> 
#include "OLED.h"
#include "ADS1256.h"
#include "FFT.h"
#include "EXTRACTION.h"
#include "msp_ad.h"
#include "draw.h"
#include "AD9850.h"

double ADS1256_Voltage;
unsigned char real[10];
unsigned int result;
float SIN_TAB[FFT_N/4+1];
unsigned int  zhi[FFT_N];
float mo[FFT_N];
float feature[5];
float history[6]={1, 2, 3, 4, 5, 6};;
//对应的权重分别为：1/21， 2/21， 3/21，  4/21，  5/21，  6/21
unsigned char kF[6]={1, 2, 3, 4, 5, 6};
uint32_t FSC = 0;
int32_t OFC = 0;
unsigned int count=0;
//unsigned int dds=15000;
unsigned char vol3[10] ={0};
unsigned char vol1[4] ={0};
unsigned char vol2[7] ={0};
unsigned char flag_Ad=0;
unsigned int Overflow_counter,Input_one_capture,rua,data_counter,Input_one_capture2,dr;
unsigned long Avarage_period,Avarage_width;
unsigned int adValue[2048];
double nowFrq=10000;
unsigned int amp[2048],ampDB[2048];
unsigned int adValueAss[2048];
unsigned int step=100;

void clkInit();
void FTC(float temp,unsigned char *real);
float TaskSampCtrl();
void timer_init();
unsigned long realzhi(unsigned long l);
void to_string(unsigned long l);

void main(void)
{
    //WDTCTL = WDTPW | WDTHOLD;
    unsigned int i;
    clkInit();
    OLED_Init();
    OLED_Clear();
    ad9850_reset();
    ad_init();
    //ADS1256_Init(0x01,1,30000);
    //timer_init();
    while(1)
    {             
          //wait();
          /*OLED_ShowString(10,0,"--LRC TEST--");
          frequency_extraction(temp,feature);
          ADS1256_Voltage = TaskSampCtrl();
          FTC(ADS1256_Voltage,real);
          OLED_ShowString(0,2,real);          
          FTC(feature[0],real);
          OLED_ShowString(60,2,real);          
          OLED_ShowString(0,4,"Fre:");
          OLED_ShowNum(60,4,count,3,12);*/
          //temp = ADS1256_Read_a_Data();
          //getcalibration();
          //delay_us(50);
          //FTC(temp,real);
          //OLED_ShowString(0,4,real);
          //OLED_ShowString(65,4,"   :Vol");
          //OLED_ShowString(0,6,mo);
          //ad9850_wr_serial(0x00,20000);
          //to_string(realzhi(Avarage_period));
          //dr=Avarage_width*10000/Avarage_period;
          //dr=Avarage_period;
           /*vol2[0]=dr/1000+'0';
           vol2[1]=dr/100%10+'0';
           vol2[2]='.';
           vol2[3]=dr/10%10+'0';
           vol2[4]=dr%10+'0';
           vol2[5]='%';
           vol2[6]='\0';
          OLED_ShowString(0,0,vol2);*/  
      OLED_ShowString(10,0,"--LRC TEST--");
          /*for(i=0;i<FFT_N;i++)
          {
            zhi[i] = ADS1256_Read_a_Data();
            //delay_us(1);        //1us取样
          }
          FTC(ADS1256_Voltage,real);
          OLED_ShowString(0,2,real);          
          FTC(feature[1],real);
          OLED_ShowString(60,2,real);          
          FTC(feature[2],real);
          OLED_ShowString(0,4,real);
          FTC(feature[3],real);
          OLED_ShowString(50,4,real);
          FTC(feature[4],real);
          OLED_ShowString(0,6,real);
          //OLED_ShowNum(100,6,count,2,12);
          ADS1256_Voltage = TaskSampCtrl();
          fft_2(zhi,mo,SIN_TAB);
          frequency_extraction(mo,feature);*/
          //ad9850_wr_serial(0x00,10000);
          //ADS1256_Voltage = TaskSampCtrl();
          //FTC(ADS1256_Voltage,real);
          //OLED_ShowString(0,2,real); 
          OLED_ShowNum(100,6,count,2,12);
          count++;
          //flag_Ad++;
          ftcompute();
          /*if(flag_Ad==10){
             adGet1000(0x01,1,30000);
             flag_Ad=0;
          }*/
          //OLED_ShowString(0,2,adValue);
      
    }
}

/*#pragma vector=TIMER2_A1_VECTOR
__interrupt void TIMER2_A1_ISR(void)
{
      switch(TA2IV)
	{
	    case 2:
	        Avarage_period = (Overflow_counter-data_counter)*65536 - Input_one_capture + TA2CCR1;   // 计算周期值
                Input_one_capture = TA2CCR1;            // 保存捕获值，供下一次使用
                data_counter=Overflow_counter;                    // 溢出次数清零
                break; 
        case 4:
         Avarage_width=(Overflow_counter-data_counter)*65536 - Input_one_capture + TA2CCR2;   // 计算高电平宽度
          break;
                case 14: 
                Overflow_counter++;                  // TA每次溢出，溢出变量+1
	        break;
	}
}*/

/*#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
      dds=dds+100;
      ad9850_wr_serial(0x00,dds);
      if(dds>3000000)
        dds=0;
      TA0CCR0 = 1;
}*/

void clkInit(){
  WDTCTL=WDTPW+WDTHOLD;
  P2DIR|=BIT2;                        //smlck OUTPUT
  P2SEL|=BIT2;
  //P7DIR|=BIT7;
  //P7SEL|=BIT7;                  //MCLK OUTPUT
  //P5SEL|=BIT2+BIT3;             //高速外部xt2
  //UCSCTL6 &= ~XT2OFF;
  UCSCTL3 = SELREF_2;                       // Set DCO FLL reference = REFO  
  //UCSCTL4 &= ~SELS_4;                       //取消默认的SELS_4  
  UCSCTL4 |= SELA_2; //+ SELS_3;               //设置SMCLK = DCO  
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx  
  
  // Loop until XT1,XT2 & DCO stabilizes - In this case only DCO has to stabilize  
  do  
  {  
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);  
                                            // Clear XT2,XT1,DCO fault flags  
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags  
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag  
      
  __bis_SR_register(SCG0);                  // Disable the FLL control loop  
  UCSCTL1 = DCORSEL_5;                      // Select DCO range 16MHz operation  
  //UCSCTL2 |= FLLD_1 + 762;//FLLD_0 + 762;//380;                           // Set DCO Multiplier for 8MHz  
  //UCSCTL4 |= SELS_5 + SELM_5;////                                    // (N + 1) * FLLRef = Fdco  
   UCSCTL2 |= 249;                                         // (249 + 1) * 32768 = 8MHz  
  __bic_SR_register(SCG0);                  // Enable the FLL control loop  
}


/*void timer_init()
{                                       
  
  P2SEL |= BIT4+BIT5;                              // 选择2.4，2.5口为第二功能
  TA2CTL = TACLR;                                     // 复位定时器TA2
  TA2CTL = TASSEL_2 + ID_0 + MC_2 + TAIE;        // 时钟源为SMCLK，连续增模式             //0.125us
  TA2CCTL1 = CCIE + CAP + CCIS_0 + CM_1 + SCS;  // 通道1开捕获中断，上升沿捕获
  TA2CCTL2 = CCIE + CAP + CCIS_0 + CM_2 + SCS;  // 通道2开捕获中断,下降沿捕获
  
  TA0CCTL0 = CCIE;                           	// CCR0中断使能
  TA0CCR0 = 1;
  TA0CTL = TASSEL_2 + MC_1 + TACLR;     		// SMCLK, 增计数模式, 清除TAR 
  
   __bis_SR_register(GIE);
}
*/

void FTC(float temp,unsigned char *real){
  unsigned int ll=0;
  if(temp>=0){
  real[0]=' ';
  }else {
  real[0]='-';
  temp=-temp;
  }
  ll=(int)(temp*10000);
  real[1]=ll/10000+'0';
  real[2]='.';
  real[3]=ll/1000%10+'0';
  real[4]=ll/100%10+'0';
  //real[5]=ll/10%10+'0';
  //real[6]=ll%10+'0';
  real[5]='V';
  real[6]=' ';
   real[7]='\0';
}

float TaskSampCtrl()
{
	unsigned char m=3;
        unsigned char q=6;     //1+2+3=6
         unsigned char p;
         unsigned char i, j;
         float s,samp;
         uint32_t temp;
	//准备工作，进行M-1次采样，这样一来才可以保证第一次输出的有效采样值是正确，如果一开始这个数组只有一个有效采样值，其他值为0，则平均以后的数值肯定不正确
	for (p=0; p<m-1; p++)
	{
		temp = ADS1256_Read_a_Data();
                getcalibration();
                history[p] = computeVoltage(temp,1,30000);
                
	}
	//该循环结束之后，p = M-1
		//每次进来更新一次数据
		temp = ADS1256_Read_a_Data();
                getcalibration();
                history[p] = computeVoltage(temp,1,30000);
		p++;  //第一次进来之后，p = M
		if (p == m)
		{
			p = 0;
		}
		s = 0;
		j = p;
		for (i=0; i<m; i++)
		{
			s += kF[i]*history[j];
			j++;
			if (j==m)
			{
				j =0;
			}
		}
    return samp = s/q;
		
}
unsigned long realzhi(unsigned long l)
{
  unsigned long t;
  double temp;
  temp= 84022070/(double)l;
  t=(unsigned long)temp;
  return t;
}
void to_string(unsigned long l)
{
  vol3[0]=l%1000000/100000+'0';
  vol3[1]=l%100000/10000+'0';
  vol3[2]=l%10000/1000+'0';
  vol3[3]=l%1000/100+'0';
  vol3[4]=l%100/10+'0';
  vol3[5]='.';
  vol3[6]=l%10+'0';
   vol3[7]='H';
  vol3[8]='z';
  vol3[9]='\0';
 
}
