#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	  
#include "key.h"     
#include "usart3.h"
#include "common.h" 
#include "dht11.h" 
 
/************************************************
 ALIENTEK STM32F103������ ��չʵ��5
 ATK-RM04 WIFIģ�����ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
			    
// DATA  ---   G11
u8 temperature;  	    
u8 humidity;
	
 int main(void)
 {	 
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ������ 
	usart3_init(115200);		//��ʼ������3 
	DHT11_Init();             //��ʪ�ȴ�������ʼ��
	 while(1)
	 {								  									 
			atk_8266_wifiap_test();		//����ATK_ESP8266����
	 }
}


















