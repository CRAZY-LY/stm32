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

int now_f;        //ʵʱƵ��
int now_d;        //ʵʱƵ��
double T=0.0;    //��ʼʱ��
int c=10;       //�Ӽ��ٶ�
double St;     //���ʱ��us
long infF;     //�м�Ƶ��
double infT;   //ʱ��յ�
long StaF=1300;   // 1/830us  ��λHZ   ��ʼƵ��   1204
long MovF=1886;   // 1/530us  ��λHZ   ����Ƶ��  1886   2050



#endif
