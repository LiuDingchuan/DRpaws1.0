#include "main.h"

//CanTxMsg tx_message;


int main()
{   
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		Valve_Configuration();
		CAN1_Init();
		LED_Init();
		BEEP_Init();
		TIM3_Init();
		BEEP_Show(3);
	
 	 	for(int i=0;i<8;i++) valve[i]=0;
		while(1)
		{
			LED_Show();
    	if(valve[0]) 
				valve1ON
			else	 	
				valve1OFF
			
			if(valve[1]) 
				valve2ON 
			else 
				valve2OFF
				
			if(valve[2]) 
				valve3ON 
			else 
				valve3OFF
				
			if(valve[3]) 
				valve4ON 
			else 
				valve4OFF
				
			if(valve[4]) 
				valve5ON 
			else 
				valve5OFF
				
			if(valve[5]) 
				valve6ON 
			else 
				valve6OFF
				
			if(valve[6]) 
				valve7ON 
			else 
				valve7OFF
			
			if(valve[7])
				valve8ON
			else 
				valve8OFF
		
	}
} 

void Valve_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	GPIO_SetBits(GPIOA, GPIO_Pin_2|GPIO_Pin_3);
}

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_Config;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_Config.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_10;
	GPIO_Config.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Config);
	GPIO_SetBits(GPIOB, GPIO_Pin_11|GPIO_Pin_10);
}

void LED_Show(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_10|GPIO_Pin_11);
//	delay_ms(1000);
//	GPIO_SetBits(GPIOB, GPIO_Pin_10|GPIO_Pin_11);
//	delay_ms(1000);
	GPIO_ResetBits(GPIOB, GPIO_Pin_10|GPIO_Pin_11);
}

void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructrue;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructrue);
}

void BEEP_Show(u8 i)
{
	for(u8 cnt=0; cnt<i; cnt++)
	{
		BEEP_ON;
		delay_ms(100);
		BEEP_OFF;
		delay_ms(100);
	}
}
