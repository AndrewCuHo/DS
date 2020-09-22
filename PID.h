#ifndef _PID_H
#define _PID_H


#define ENABLE_LIMITS 1 //是否使能限幅功能
#define PID_MAX 65535
#define PID_MIN 0

typedef struct {
	float SetValue; //定义设定值
	float realvalue;//
	float out;//送往执行器输出值
	float err; //定义偏差值
	float err_last; //定义上一个偏差值
	float err_last_last; //定义最上前的偏差值
	float Kp,Ki,Kd; //定义比例、积分、微分系数
	float alpha,ud,ud_last,integral;//不完全微分系数,本次微分值，上次微分值，积分
} pid_stu;

extern pid_stu pid;

void PID_init(float set);
void PID_Set_Value(float value);
float PID(float ActuaValue);
float PID_new(float ActuaValue);



#endif
