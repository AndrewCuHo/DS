#ifndef _PID_H
#define _PID_H


#define ENABLE_LIMITS 1 //�Ƿ�ʹ���޷�����
#define PID_MAX 65535
#define PID_MIN 0

typedef struct {
	float SetValue; //�����趨ֵ
	float realvalue;//
	float out;//����ִ�������ֵ
	float err; //����ƫ��ֵ
	float err_last; //������һ��ƫ��ֵ
	float err_last_last; //��������ǰ��ƫ��ֵ
	float Kp,Ki,Kd; //������������֡�΢��ϵ��
	float alpha,ud,ud_last,integral;//����ȫ΢��ϵ��,����΢��ֵ���ϴ�΢��ֵ������
} pid_stu;

extern pid_stu pid;

void PID_init(float set);
void PID_Set_Value(float value);
float PID(float ActuaValue);
float PID_new(float ActuaValue);



#endif
