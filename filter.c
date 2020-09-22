#include "FILTER.h"
/*******************************************************
1.方法：连续采样N次(N取奇次)，把N次采样值按大小排列去中间值为有效值。这种滤波法的思路是：
		(1)不论当前采样值因为某正原因导致其偏差过大或者过小，(假设我们是按照从小到大排列)，那么排列之后
		(2)偏差过大者被排在了前边，偏差过小的被排到了后边，这样中间的就比较可信
		(3)优点：能有效克服因偶然因素引起的波动干扰；对温度，液位等变化缓慢的被测参数有良好的滤波效果
		(4)缺点：对流量、速度等快速变化的参数不宜
2.例程：如下函数unsigned char MiddleValueFilter()
		(1)调用函数
		   GetAD();该函数用来取得当前采样值
		   Delay();基本延时函数
		(2)变量说明：
		   ArrDataBuffer[N]:用来存放一次性采集的N组数据
		   Temp:完成冒泡法使用的临时寄存器
		   i,j,k:循环使用的参数值
		(3)常量说明：
		   N:数组长度
		(4)入口：
		(5)出口：
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

