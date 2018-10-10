#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	  
#include "key.h"     
#include "usart3.h"
#include "common.h" 
#include "dht11.h" 
 
/************************************************
 ALIENTEK STM32F103开发板 扩展实验5
 ATK-RM04 WIFI模块测试实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
			    
// DATA  ---   G11
u8 temperature;  	    
u8 humidity;
	
 int main(void)
 {	 
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();		  			//初始化与LED连接的硬件接口
	KEY_Init();					//初始化按键 
	usart3_init(115200);		//初始化串口3 
	DHT11_Init();             //温湿度传感器初始化
	 while(1)
	 {								  									 
			atk_8266_wifiap_test();		//进入ATK_ESP8266测试
	 }
}


















