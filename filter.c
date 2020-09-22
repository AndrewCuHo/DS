#include "FILTER.h"
/*******************************************************
1.��������������N��(Nȡ���)����N�β���ֵ����С����ȥ�м�ֵΪ��Чֵ�������˲�����˼·�ǣ�
		(1)���۵�ǰ����ֵ��Ϊĳ��ԭ������ƫ�������߹�С��(���������ǰ��մ�С��������)����ô����֮��
		(2)ƫ������߱�������ǰ�ߣ�ƫ���С�ı��ŵ��˺�ߣ������м�ľͱȽϿ���
		(3)�ŵ㣺����Ч�˷���żȻ��������Ĳ������ţ����¶ȣ�Һλ�ȱ仯�����ı�����������õ��˲�Ч��
		(4)ȱ�㣺���������ٶȵȿ��ٱ仯�Ĳ�������
2.���̣����º���unsigned char MiddleValueFilter()
		(1)���ú���
		   GetAD();�ú�������ȡ�õ�ǰ����ֵ
		   Delay();������ʱ����
		(2)����˵����
		   ArrDataBuffer[N]:�������һ���Բɼ���N������
		   Temp:���ð�ݷ�ʹ�õ���ʱ�Ĵ���
		   i,j,k:ѭ��ʹ�õĲ���ֵ
		(3)����˵����
		   N:���鳤��
		(4)��ڣ�
		(5)���ڣ�
********************************************************/


 unsigned int MiddleValueFilter(unsigned int *ArrDataBuffer)
{
	unsigned char i, j, k;
	unsigned int Temp;
	
	for (j=0; j<N-1; j++)
	{
		for (k=0; k<N-j-1; k++)
		{
			if (ArrDataBuffer[k] > ArrDataBuffer[k+1])
			{
				Temp = ArrDataBuffer[k];
				ArrDataBuffer[k] = ArrDataBuffer[k+1];
				ArrDataBuffer[k+1] = Temp;
			}	
		}
	}
	
	return ArrDataBuffer[(N-1)/2];
}

