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
 ALIENTEK战舰STM32开发板实验9
 PWM输出实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


//double band_list[];
//  调试笔记    数据处理   int double 类型同时进行算数确定好最终是什么数据，必要时需将2变成2.0！！！
u16 t;
double Rt;
int buffer[1000];
 int main(void)
 {		
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 
	uart_init(115200);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
 	TIM3_PWM_Init(now_f*2,71);	
	 TIM2_Int_Init();
	 GPIO_ResetBits(GPIOA,GPIO_Pin_6);	//DIR
	 GPIO_SetBits(GPIOC,GPIO_Pin_4);	//SLEEP
	 GPIO_ResetBits(GPIOC,GPIO_Pin_5);	//ENABLE
	 usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART	
	 Band_ListCreat(1000);
   	while(1)
	{		
		   TIM_SetCompare2(TIM3,now_f);
		  	  
	}	 
 }
 //频段表建立函数，参数为：加加速度系数 c
void Band_ListCreat (int c)
{
	St=2.0/StaF;   //累加时间间隔
	Rt=St*1000000.0;
	infF=(StaF+MovF)/2.0;           //拐点频率
	infT=sqrt((infF-StaF)*2.0/c);  //拐点时间
	now_d=now_f+1;
	while(T<infT)             //第一段速度函数
		{
			now_f=StaF+c*T*T/2;
			buffer[t]=now_f;         //将频率值放在生成的内存中
			t++;               //累加计算数值个数
			T=T+St;           //时刻T		
		}
		while(1)           //第二段速度函数
		{
			now_f=2*c*T*infT-c*T*T/2-2*infF+3*StaF;
			buffer[t]=now_f;         //将频率值放在生成的内存中
			t++;               //累加计算数值个数
			T=T+St;           //时刻T
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
	t=0;        //计数清零
	MovF=x;    //设置新的运行频率
	Band_ListCreat(1000);//生成新的频段表
	
}
