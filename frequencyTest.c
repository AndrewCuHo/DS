/*
 * frequencyTest.c
 *
 *  Created on: 2019Äê8ÔÂ5ÈÕ
 *      Author: 09050220
 */

#include "frequencyTest.h"


void ftstart(){
    uint32_t i;
    for(i=0;i<4;i++){
      while ((ADC12IFG & ADC12BUSY)==0);
        adValue[i] = ADC12MEM0;
    }
    if(nowFrq<20000){
        for(i=0;i<256;i++){
           while ((ADC12IFG & ADC12BUSY)==0);
            adValueAss[i] = ADC12MEM0;
        }
    }else if(nowFrq<50000){
        for(i=0;i<64;i++){
            while ((ADC12IFG & ADC12BUSY)==0);
        adValueAss[i] = ADC12MEM0;
        }
    }else if(nowFrq<100000){
        for(i=0;i<32;i++){
            while ((ADC12IFG & ADC12BUSY)==0);
        adValueAss[i] = ADC12MEM0;
        }
    }else if(nowFrq<200000){
        for(i=0;i<8;i++){
            while ((ADC12IFG & ADC12BUSY)==0);
        adValueAss[i] = ADC12MEM0;
        }
    }
    ad9850_wr_serial(0x00,nowFrq+step);
    if(step == 1000){
        delay_us(100);
    }
}

void ftcompute(){
    uint32_t i = 0,umax = 0,umin = 0xFFFFFFFF,bias = 0,count = 0;
    nowFrq = 1000;
    for(i = 0 ;i < 1000 ;i++){
        ampDB[i] = 0;
    }
    for(i = 0 ;i < 1000 ;i++){
        amp[i] = 0;
    }
    ad9850_wr_serial(0x00,nowFrq);
		delay_us(100);
    while(nowFrq <= 1000000){
        ftstart();
        umax = adValue[0];
        umin = adValue[0];
        if(nowFrq < 120000){
            for(i=0;i<32;i++){
                if(adValue[i] > umax && (abs(adValue[i] - umax) < 200)){
                    umax = adValue[i];
                }
                if(adValue[i] < umin && (abs(adValue[i] - umin) < 200)){
                    umin = adValue[i];
                }
            }
        }else{
            for(i=0;i<32;i++){
                        if(adValue[i] > umax){
                            umax = adValue[i];
                        }
                        if(adValue[i] < umin){
                            umin = adValue[i];
                        }
            }
        }
       if(nowFrq<20000){
            for(i=0;i<2048;i++){
                if(adValueAss[i] > umax&& (abs(adValueAss[i] - umax) < 50)){
                    umax = adValueAss[i];
                }
                if(adValueAss[i] < umin && (abs(adValueAss[i] - umin) < 50)){
                    umin = adValueAss[i];
                }
            }
        }else if(nowFrq<50000){
            for(i=0;i<512;i++){
                if(adValueAss[i] > umax&& (abs(adValueAss[i] - umax) < 200)){
                    umax = adValueAss[i];
                }
                if(adValueAss[i] < umin&& (abs(adValueAss[i] - umin) < 200)){
                    umin = adValueAss[i];
                }
            }
        }else if(nowFrq<100000){
            for(i=0;i<256;i++){
                if(adValueAss[i] > umax&& (abs(adValueAss[i] - umax) < 200)){
                    umax = adValueAss[i];
                }
                if(adValueAss[i] < umin&& (abs(adValueAss[i] - umin) < 200)){
                    umin = adValueAss[i];
                }
            }
        }else if(nowFrq<200000){
            for(i=0;i<64;i++){
                if(adValueAss[i] > umax&& (abs(adValueAss[i] - umax) < 200)){
                    umax = adValueAss[i];
                }
                if(adValueAss[i] < umin&& (abs(adValueAss[i] - umin) < 200)){
                    umin = adValueAss[i];
                }
            }
        }

       if((nowFrq/step - bias) > 999){
           while((int)(pow(10,3*(count+(1))/1000.0)*(1000/step)+0.5) - bias < 1000){
               ampDB[count] = amp[(int)(pow(10,3*(count+(1))/1000.0)*(1000/step)+0.5) - bias - 1];
               count ++ ;
           }
           bias += 999;
       }
        amp[((int)nowFrq/step)-bias-1] = umax - umin;
        ampDB[(int)(1000.0*log10(nowFrq/1000)/3) -1] = umax - umin;

        nowFrq += step;
    }
    nowFrq = 1000;
}

void AmptoDB(){
    int i;
    for (i = 0; i < 1000 ; i++){
        //ampDB[i] = 20 * (uint32_t)( log10((float)amp[(int)(pow(10,3*(i+1)/1000)+0.5) - 1] / 1340.0) ) + 100;
      //  ampDB[i] = amp[(int)(pow(10,3*(i+1)/1000.0)+0.5) - 1] ;
    }
}

