#ifndef __CAN1_H
#define __CAN1_H

#include "stdbool.h"
#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include "stm32f10x_rcc.h"

#define valve1OFF  GPIO_SetBits(GPIOB, GPIO_Pin_1);//SetBits是设置高电平，RESETBITS是设置低电平，但为什么这里设置高电平之后电磁阀是不通电的状态呢？
#define valve1ON GPIO_ResetBits(GPIOB, GPIO_Pin_1);//答：与设计的电路有关。这个板子设计的时候IO口固定端是高电平，所以只有当设置IO口拉低的时候，才会有电流通过，才能使它上电
#define valve2OFF  GPIO_SetBits(GPIOB, GPIO_Pin_0);//感谢杨震学长的解答！
#define valve2ON GPIO_ResetBits(GPIOB, GPIO_Pin_0);
#define valve3OFF  GPIO_SetBits(GPIOA, GPIO_Pin_3);
#define valve3ON GPIO_ResetBits(GPIOA, GPIO_Pin_3);
#define valve4OFF  GPIO_SetBits(GPIOA, GPIO_Pin_2);
#define valve4ON GPIO_ResetBits(GPIOA, GPIO_Pin_2);

#define valve5ON  GPIO_ResetBits(GPIOB, GPIO_Pin_4);
#define valve5OFF GPIO_SetBits(GPIOB, GPIO_Pin_4);
#define valve6ON  GPIO_ResetBits(GPIOB, GPIO_Pin_5);
#define valve6OFF GPIO_SetBits(GPIOB, GPIO_Pin_5);
#define valve7ON  GPIO_ResetBits(GPIOB, GPIO_Pin_6);
#define valve7OFF GPIO_SetBits(GPIOB, GPIO_Pin_6);
#define valve8ON  GPIO_ResetBits(GPIOB, GPIO_Pin_7);
#define valve8OFF GPIO_SetBits(GPIOB, GPIO_Pin_7);

//防御手爪标志位
typedef struct{
	bool LeftHand;  
	bool LeftPaw;   
	bool RightHand; 
	bool RightPaw;  
	
	bool LeftHandPrv;
	bool LeftPawPrv;
	bool RightHandPrv;
	bool RightPawPrv;
	
	bool LeftHandCounting;
	bool LeftPawCounting;
	bool RightHandCounting;
	bool RightPawCounting;
	
	bool isLeftHandFinished;
	bool isLeftPawFinished;
	bool isRightHandFinished;
	bool isRightPawFinished;

	u16 LeftHandcnt;
	u16 LeftPawcnt;
	u16 RightHandcnt;
	u16 RightPawcnt;
	u16 RighthandStrectchcnt;
}FlagTypedef;

typedef struct
{
	volatile u8 prio;//优先级编码，ID24-ID26，0x00-0x07
	
	volatile u8 mastermacid;//源节点编码，ID16-ID23，0x01-0xff
	
	volatile u8 selfmacid;//目标节点编码，ID8-ID15,0x01-0xff(0x00用于发送广播帧)
	
	volatile u8 ack;//响应标志位，ID0，0用于命令帧，1用于响应帧
	
}can_id_dataTypeDef;

void CAN1_Init(void);
void answer_master(CanRxMsg *rx_message);
extern bool valve[8];
extern FlagTypedef flag;
#endif
