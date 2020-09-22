#ifndef PWM_H_
#define PWM_H_

extern unsigned int spwm_i,spwm_j;
extern unsigned int Lab_base[];
extern unsigned int Lab1[];

extern void SPWM_1Way_Init(void);
extern void SPWM_1Way_Set_Freq(unsigned int freq);
extern void SPWM_2Way_Init(void);
extern void SPWM_2Way_Set_Freq(unsigned int freq);

#endif /* PWM_H_ */