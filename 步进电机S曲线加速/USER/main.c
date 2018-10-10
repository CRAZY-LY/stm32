#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "usmart.h"	
#include "sram.h"
#include "malloc.h"
#include "main.h"
#include "math.h"
#include "string.h"



/************************************************
 ALIENTEKս��STM32������ʵ��9
 PWM���ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


//double band_list[];
//  ���Աʼ�    ���ݴ���   int double ����ͬʱ��������ȷ����������ʲô���ݣ���Ҫʱ�轫2���2.0������
u16 t;
double Rt;
int buffer[1000];
 int main(void)
 {		
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
 	TIM3_PWM_Init(now_f*2,71);	
	 TIM2_Int_Init();
	 GPIO_ResetBits(GPIOA,GPIO_Pin_6);	//DIR
	 GPIO_SetBits(GPIOC,GPIO_Pin_4);	//SLEEP
	 GPIO_ResetBits(GPIOC,GPIO_Pin_5);	//ENABLE
	 usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART	
	 Band_ListCreat(1000);
   	while(1)
	{		
		   TIM_SetCompare2(TIM3,now_f);
		  	  
	}	 
 }
 //Ƶ�α�������������Ϊ���Ӽ��ٶ�ϵ�� c
void Band_ListCreat (int c)
{
	St=2.0/StaF;   //�ۼ�ʱ����
	Rt=St*1000000.0;
	infF=(StaF+MovF)/2.0;           //�յ�Ƶ��
	infT=sqrt((infF-StaF)*2.0/c);  //�յ�ʱ��
	now_d=now_f+1;
	while(T<infT)             //��һ���ٶȺ���
		{
			now_f=StaF+c*T*T/2;
			buffer[t]=now_f;         //��Ƶ��ֵ�������ɵ��ڴ���
			t++;               //�ۼӼ�����ֵ����
			T=T+St;           //ʱ��T		
		}
		while(1)           //�ڶ����ٶȺ���
		{
			now_f=2*c*T*infT-c*T*T/2-2*infF+3*StaF;
			buffer[t]=now_f;         //��Ƶ��ֵ�������ɵ��ڴ���
			t++;               //�ۼӼ�����ֵ����
			T=T+St;           //ʱ��T
			if(now_f>=MovF-1)
				break;
		}
}
void TIM2_arr(int x,int y)
{
	TIM2->ARR=x;
	now_f=y;
}
void Mov_F (int x)
{
	MovF=x;
}
void Reset_data (int x)
{
	t=0;        //��������
	MovF=x;    //�����µ�����Ƶ��
	Band_ListCreat(1000);//�����µ�Ƶ�α�
	
}
