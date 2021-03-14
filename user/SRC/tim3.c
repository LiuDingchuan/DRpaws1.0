#include "tim3.h"

void TIM3_Init()
{
	TIM_TimeBaseInitTypeDef TIM3_Structure;
	NVIC_InitTypeDef NVIC_InitStructure;	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		
	TIM3_Structure.TIM_Period = 72-1;	
	TIM3_Structure.TIM_Prescaler = 1000-1;	
	TIM3_Structure.TIM_ClockDivision = 0;
	TIM3_Structure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM3_Structure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}

void TIM3_IRQHandler()
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)//溢出中断
	{
		if(flag.LeftHandCounting)
		{
			flag.LeftHandcnt++;
			if(flag.LeftHandcnt>=650)
			{
				flag.isLeftHandFinished=true;
				flag.LeftHandCounting=false;
				flag.LeftHandPrv=flag.LeftHand;
				flag.LeftHandcnt=0;
			}		
		}
		if(flag.LeftPawCounting)
		{
			flag.LeftPawcnt++;
			if(flag.LeftPawcnt>=20)
			{
				flag.isLeftPawFinished=true;
				flag.LeftPawCounting=false;
				flag.LeftPawPrv=flag.LeftPaw;
				flag.LeftHandcnt=0;
			}
		}
		if(flag.RightHandCounting)
		{
			flag.RighthandStrectchcnt++;
			if(flag.RightHand==true)
			{
				if(flag.RighthandStrectchcnt>=500)
				{
					valve[1]=1;
					flag.RightHandcnt++;
				}
				if(flag.RightHandcnt>=1600)
				{					
					flag.isRightHandFinished=true;
					flag.RightHandCounting=false;
					flag.RightHandPrv=flag.RightHand;
					flag.RightHandcnt=0;
				}
			}
			else
			{
				flag.RighthandStrectchcnt++;
				if(flag.RighthandStrectchcnt>=500)
				{
					valve[1]=0;
					flag.RightHandcnt++;
				}
				if(flag.RightHandcnt>=1600)
				{
					flag.isRightHandFinished=true;
					flag.RightHandCounting=false;
					flag.RightHandPrv=flag.RightHand;
					flag.RightHandcnt=0;
				}		
			}
		}	
		if(flag.RightPawCounting)
		{
			flag.RightPawcnt++;
			if(flag.RightPawcnt>=20)
			{
				flag.isRightPawFinished=true;
				flag.RightPawCounting=false;
				flag.RightPawPrv=flag.RightPaw;
				flag.RightPawcnt=0;
			}
		}
	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //清除中断标志位
}	
		
	
	
	
	
	
	
	
	



