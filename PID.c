#include "PID.h"

pid_stu pid;//声明pid设置结构体
void PID_init(float set){
	pid.SetValue = set;
	pid.out=0.0;
	pid.err = 0.0;
	pid.err_last_last = 0.0;
	pid.err_last = 0.0;
	pid.Kp = 100.0;
	pid.Ki = 10.0;
	pid.Kd = 10.0;
	pid.alpha=0.0;
	pid.ud=0.0;
	pid.ud_last=0.0;
	pid.integral=0.0;
}

void PID_Set_Value(float value){
		pid.SetValue = value;
}




//根据实际输入（ActuaValue）计算输出并返回
float PID(float ActuaValue){
	float increment;
	pid.realvalue=ActuaValue;
	pid.err = pid.SetValue-ActuaValue;
	increment = pid.Kp*(pid.err-pid.err_last)+pid.Ki*pid.err
		+pid.Kd*(pid.err-2*pid.err_last+pid.err_last_last);
	pid.out += increment;
	
	#if ENABLE_LIMITS
	if(pid.out>PID_MAX)
		pid.out=PID_MAX;
	if(pid.out<PID_MIN)
		pid.out=PID_MIN;
	#endif
	
	pid.err_last_last = pid.err_last;
	pid.err_last = pid.err;
	return pid.out;
}
float PID_new(float ActuaValue){
	pid.err = pid.SetValue-ActuaValue;
	pid.ud = pid.Kd * (1 - pid.alpha) * (pid.err - pid.err_last) + pid.alpha * pid.ud_last;
    pid.out = pid.Kp * pid.err + pid.Ki * pid.integral + pid.ud;
    pid.err_last = pid.err;
    pid.ud_last = pid.ud;
    pid.integral += pid.err;
	#if ENABLE_LIMITS
	if(pid.out>PID_MAX)
		pid.out=PID_MAX;
	if(pid.out<PID_MIN)
		pid.out=PID_MIN;
	#endif
	return pid.out;
}

