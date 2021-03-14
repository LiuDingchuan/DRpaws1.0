#include "can1.h"

bool valve[8];
FlagTypedef flag;

void CAN1_Init(void)
{
	CAN_InitTypeDef CAN_InitStruct;
	GPIO_InitTypeDef GPIO_InitStucture;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);												//使能CAN1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);											//使能PORTA时钟

	GPIO_InitStucture.GPIO_Mode=GPIO_Mode_AF_PP;															//复用推挽
	GPIO_InitStucture.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStucture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStucture);
	
	GPIO_InitStucture.GPIO_Mode=GPIO_Mode_IPU;															//一个要拉高电平
	GPIO_InitStucture.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStucture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStucture);
		
	CAN_InitStruct.CAN_ABOM=DISABLE;																				//软件自动离线管理
	CAN_InitStruct.CAN_AWUM=DISABLE;																				//睡眠模式通过软件唤醒
	CAN_InitStruct.CAN_BS1=CAN_BS1_4tq;																			//时间段1占用时间单位
	CAN_InitStruct.CAN_BS2=CAN_BS2_4tq;																			//时间段2占用时间单位
	CAN_InitStruct.CAN_Mode=CAN_Mode_Normal;																						//模式设置：0，普通模式；1，回回环模式
	CAN_InitStruct.CAN_NART=ENABLE;																					//禁止报文自动传送
	CAN_InitStruct.CAN_Prescaler=4;																				//分频系数(Fdiv)为brp+1
	CAN_InitStruct.CAN_RFLM=DISABLE;																				//报文不锁定，新的覆盖旧的
	CAN_InitStruct.CAN_SJW=CAN_SJW_1tq;																						//重新同步跳跃宽度
	CAN_InitStruct.CAN_TTCM=DISABLE;																				//非时间触发通信模式
	CAN_InitStruct.CAN_TXFP=DISABLE;																				//优先级由报文标识符确定
	CAN_Init(CAN1,&CAN_InitStruct);
	
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;											//激活过滤器0
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;	
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterIdHigh=((0x00010400<<3)&0xffff0000)>>16;			//32位ID
	CAN_FilterInitStructure.CAN_FilterIdLow=(0x00010400<<3)&0xffff;														
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=(0xffff0000<<3)>>16;					//32位MASK
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=(0xffff00<<3)&0xffff;
	CAN_FilterInitStructure.CAN_FilterNumber=0;																//过滤器0
	CAN_FilterInit(&CAN_FilterInitStructure);

	CAN_FilterInitStructure.CAN_FilterNumber = 1; //屏蔽位模式
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh =((0x00010000 << 3) & 0xFFFF0000) >> 16;
	CAN_FilterInitStructure.CAN_FilterIdLow = (0x00010000 << 3) & 0xFFFF;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (0xFFFF0000 << 3) >> 16;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = (0xFFFF0000 << 3) & 0xFFFF;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_FilterInitStructure.CAN_FilterNumber = 2; //屏蔽位模式
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = ((0x01314155 << 3) & 0xFFFF0000) >> 16;
	CAN_FilterInitStructure.CAN_FilterIdLow = (0x01314155 << 3) & 0xFFFF;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (0xffff00 << 3) >> 16;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = (0xffff	<< 3) & 0xFFFF;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     						// 主优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;								          // 次优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);		

//	
//	CAN_FilterInitStructure.CAN_FilterNumber = 1;
//	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
//	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
//	CAN_FilterInitStructure.CAN_FilterIdHigh=((0x00020001<<3)&0xffff0000)>>16;	//主控板发给舵机板的报文过滤器设置
//	CAN_FilterInitStructure.CAN_FilterIdLow=(0x00020001<<3)&0xffff;
//	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=(0xffff00<<3)>>16;							   
//	CAN_FilterInitStructure.CAN_FilterMaskIdLow=(0xffff00<<3)&0xffff;
//	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
//	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
//	CAN_FilterInit(&CAN_FilterInitStructure);
//	
//	CAN_FilterInitStructure.CAN_FilterNumber = 2;
//	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
//	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
//	CAN_FilterInitStructure.CAN_FilterIdHigh=((0x00010000<<3)&0xffff0000)>>16;
//	CAN_FilterInitStructure.CAN_FilterIdLow=(0x00010000<<3)&0xffff;
//	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=(0xffff00<<3)>>16;							   
//	CAN_FilterInitStructure.CAN_FilterMaskIdLow=(0xffff00<<3)&0xffff;
//	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
//	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
//	CAN_FilterInit(&CAN_FilterInitStructure);

//	NVIC_initstructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;    
//	NVIC_initstructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_initstructure.NVIC_IRQChannelSubPriority = 3;
//	NVIC_initstructure.NVIC_IRQChannelCmd = ENABLE;    
//	NVIC_Init(&NVIC_initstructure);	 

//	NVIC_initstructure.NVIC_IRQChannel = CAN1_RX1_IRQn;    
//	NVIC_initstructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_initstructure.NVIC_IRQChannelSubPriority = 3;
//	NVIC_initstructure.NVIC_IRQChannelCmd = ENABLE;    
//	NVIC_Init(&NVIC_initstructure);
//	
//	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
//	CAN_ITConfig(CAN1,CAN_IT_FMP1,ENABLE);
}

static CanRxMsg rx_message;
static void answer_master(CanRxMsg *rx_message);
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0) != RESET)
	{
	  CAN_Receive(CAN1,CAN_FIFO0,&rx_message);
	  CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);
	  CAN_ClearFlag(CAN1, CAN_IT_FMP0);
		
		if((rx_message.IDE == CAN_Id_Extended)&&(rx_message.RTR == CAN_RTR_Data))
		{
			if(rx_message.ExtId==0x01314155)
			{
				if(rx_message.Data[0]=='S'&&rx_message.Data[1]=='W')
				{
					flag.LeftHand=rx_message.Data[2];
					flag.RightHand=rx_message.Data[3];
					flag.LeftPaw=rx_message.Data[4];
					flag.RightPaw=rx_message.Data[5];
					//左侧手爪伸出1，收回0
					if(flag.LeftHand!=flag.LeftHandPrv)
					{
						if(flag.LeftHand==true)
							valve[0]=1;
						else
							valve[0]=0;
						flag.LeftHandCounting=true;
						flag.isLeftHandFinished=false;
					}
					else
					{
						flag.isLeftHandFinished=true;
					}
					//右侧手爪伸出1，收回0
					if(flag.RightHand!=flag.RightHandPrv)
					{
						if(flag.RightHand==true)
						{
							valve[7]=1;
						}
						else
						{
							valve[7]=0;
						}
						flag.RightHandCounting=true;
						flag.isRightHandFinished=false;
					}
					else
					{
						flag.isRightHandFinished=true;
					}
					//左侧手爪闭合1，松开0
					if(flag.LeftPaw!=flag.LeftPawPrv)
					{
						if(flag.LeftPaw==true)
							valve[2]=1;
						else
							valve[2]=0;
						flag.LeftPawCounting=true;
						flag.isLeftPawFinished=false;
					}
					else
					{
						flag.isLeftPawFinished=true;
					}
					//右侧手爪闭合1，松开0
					if(flag.RightPaw!=flag.RightPawPrv)
					{
						if(flag.RightPaw==true)
							valve[3]=1;
						else
							valve[3]=0;
						flag.RightPawCounting=true;
						flag.isRightPawFinished=false;
					}
					else
					{
						flag.isRightPawFinished=true;
					}
					answer_master(&rx_message);
				}
			}
			if(rx_message.ExtId==0x00010400)
			{
				if(rx_message.Data[0]==0x00)
				{
					if((rx_message.Data[1]=='C')&&(rx_message.Data[2]=='W')&&(rx_message.Data[3]=='H')&&(rx_message.Data[4]=='U'))
						answer_master(&rx_message);
				}
				else if(rx_message.Data[0]==0x04)
				{
					if((rx_message.Data[1]==('O'+0x40))&&(rx_message.Data[2]=='N'))//气缸开
					{
						valve[rx_message.Data[3]-1]=1;
						answer_master(&rx_message);
					}          
					else if((rx_message.Data[1]==('E'+0x40))&&(rx_message.Data[2]=='F'))//气缸关
					{
							valve[rx_message.Data[3]-1]=0;
							answer_master(&rx_message);
					}  
					else if((rx_message.Data[1]==('N'+0x40))&&(rx_message.Data[2]=='O')&&(rx_message.Data[3]=='W'))//气缸状态查询
					{
						CanTxMsg tx_message;
						tx_message.ExtId =0x00040101;
						tx_message.RTR = CAN_RTR_Data;
						tx_message.IDE = CAN_Id_Extended;
						tx_message.DLC = 8;
						tx_message.Data[0] = rx_message.Data[0] + 0x80;
						tx_message.Data[1] = rx_message.Data[1];
						tx_message.Data[2] = rx_message.Data[2];
						tx_message.Data[3] = rx_message.Data[3];
						tx_message.Data[4] = rx_message.Data[4];
						tx_message.Data[5] = valve[rx_message.Data[4]-1];      
						CAN_Transmit(CAN1,&tx_message);
					}
				}
			}
		}
  }
}


static void answer_master(CanRxMsg *rx_message)
{
	CanTxMsg tx_message;
	if(rx_message->ExtId==0x00010400)
	{
		tx_message.ExtId =0x00040101;
		tx_message.RTR = CAN_RTR_Data;
		tx_message.IDE = CAN_Id_Extended;
		tx_message.DLC = rx_message->DLC;
		tx_message.Data[0] = rx_message->Data[0] + 0x40;
		tx_message.Data[1] = rx_message->Data[1];
		tx_message.Data[2] = rx_message->Data[2];
		tx_message.Data[3] = rx_message->Data[3];
		tx_message.Data[4] = rx_message->Data[4];
		tx_message.Data[5] = rx_message->Data[5];
		tx_message.Data[6] = rx_message->Data[6];
		tx_message.Data[7] = rx_message->Data[7];		
	}
	if(rx_message->ExtId==0x01314155)
	{
		tx_message.ExtId=0x05141315;
		tx_message.RTR=CAN_RTR_DATA;
		tx_message.IDE=CAN_Id_Extended;
		tx_message.DLC=6;
		tx_message.Data[0]='S';
		tx_message.Data[1]='W';
		tx_message.Data[2]=flag.isLeftHandFinished;
		tx_message.Data[3]=flag.isRightHandFinished;
		tx_message.Data[4]=flag.isLeftPawFinished;
		tx_message.Data[5]=flag.isRightPawFinished;
	}
	CAN_Transmit(CAN1,&tx_message);
}
