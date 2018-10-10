#ifndef __MAIN_H
#define __MAIN_H
#include "sys.h"


typedef struct 
{
	long bandF;
	long bandP;
	long TotalP;
}BAND;
typedef enum 
{
	Finished=0,
	Failed
}status;
void Band_ListCreat (int c);
void TIM2_arr(int x,int y);
void Mov_F (int x);
void Reset_data (int x);

int now_f;        //实时频率
int now_d;        //实时频率
double T=0.0;    //开始时间
int c=10;       //加加速度
double St;     //间隔时间us
long infF;     //中间频率
double infT;   //时间拐点
long StaF=1300;   // 1/830us  单位HZ   开始频率   1204
long MovF=1886;   // 1/530us  单位HZ   运行频率  1886   2050



#endif
