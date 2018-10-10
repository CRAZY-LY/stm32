#include "common.h"
#include "dht11.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//ATK-ESP8266 WIFIģ�� WIFI AP��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/4/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 


//ATK-ESP8266 WIFI AP����
//���ڲ���TCP/UDP����
//����ֵ:0,����
//    ����,�������
extern u8 temperature;  
extern u8 humidity;
u8 atk_8266_wifiap_test(void)
{
	u8 key;
	u8 netpro=0;	//����ģʽ
	u8 *p;
	u16 t=999;		//���ٵ�һ�λ�ȡ����״̬
	u8 res=0;
	u16 rlen=0;
	u8 constate=0;	//����״̬
	p=mymalloc(SRAMIN,32);							//����32�ֽ��ڴ�
	atk_8266_send_cmd("AT+CWMODE=2","OK",50);		//����WIFI APģʽ
	atk_8266_send_cmd("AT+RST","OK",20);		//DHCP�������ر�(��APģʽ��Ч) 
	delay_ms(1000);         //��ʱ3S�ȴ������ɹ�
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	//�������ӵ���WIFI��������/���ܷ�ʽ/����,�⼸��������Ҫ�������Լ���·�������ý����޸�!! 
	sprintf((char*)p,"AT+CWSAP=\"%s\",\"%s\",1,4",wifiap_ssid,wifiap_password);//�������߲���:ssid,����,ͨ���ţ�����
	while(atk_8266_send_cmd(p,"OK",300));					
	
	atk_8266_send_cmd("AT+CIPMUX=1","OK",20);   //0�������ӣ�1��������
	sprintf((char*)p,"AT+CIPSERVER=1,%s",(u8*)portnum);
	atk_8266_send_cmd(p,"OK",20);     //����Serverģʽ���˿ں�Ϊ8086
	
	while(1)
	{
		DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ					    
      printf("\r\n temperature :%d",temperature);	
			printf("\r\n humidity :%d",humidity);	
		//sprintf((char*)p,"ATK-8266%s����%02d\r\n",ATK_ESP8266_WORKMODE_TBL[netpro],t/10);//��������
		sprintf((char*)p,"�¶��ǣ�%d��ʪ���ǣ�%d \r\n",temperature,humidity);//��������
		atk_8266_send_cmd("AT+CIPSEND=0,25","OK",200);  //����ָ�����ȵ�����
		delay_ms(200);
		atk_8266_send_data(p,"OK",100);  //����ָ�����ȵ�����


	if(USART3_RX_STA&0X8000)		//���յ�һ��������
	{ 
		rlen=USART3_RX_STA&0X7FFF;	//�õ����ν��յ������ݳ���
		USART3_RX_BUF[rlen]=0;		//��ӽ����� 
		printf("%s",USART3_RX_BUF);	//���͵�����   
		USART3_RX_STA=0;
		if(constate!='+')t=1000;		//״̬Ϊ��δ����,������������״̬
		else t=0;                   //״̬Ϊ�Ѿ�������,10����ټ��
	}  
	if(t==1000)//����10����û���յ��κ�����,��������ǲ��ǻ�����.
	{
		constate=atk_8266_consta_check();//�õ�����״̬
		if(constate=='+')
		printf("���ӳɹ�\r\n");	
		 //����״̬
		else printf("����ʧ�ܡ\\r\n");		  	 
		t=0;
	}
	if((t%20)==0)LED0=!LED0;
	atk_8266_at_response(1);

}
	return res;		
} 







