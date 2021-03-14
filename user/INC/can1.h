#ifndef __CAN1_H
#define __CAN1_H

#include "stdbool.h"
#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include "stm32f10x_rcc.h"

#define valve1OFF  GPIO_SetBits(GPIOB, GPIO_Pin_1);//SetBits�����øߵ�ƽ��RESETBITS�����õ͵�ƽ����Ϊʲô�������øߵ�ƽ֮���ŷ��ǲ�ͨ���״̬�أ�
#define valve1ON GPIO_ResetBits(GPIOB, GPIO_Pin_1);//������Ƶĵ�·�йء����������Ƶ�ʱ��IO�ڹ̶����Ǹߵ�ƽ������ֻ�е�����IO�����͵�ʱ�򣬲Ż��е���ͨ��������ʹ���ϵ�
#define valve2OFF  GPIO_SetBits(GPIOB, GPIO_Pin_0);//��л����ѧ���Ľ��
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

//������צ��־λ
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
	volatile u8 prio;//���ȼ����룬ID24-ID26��0x00-0x07
	
	volatile u8 mastermacid;//Դ�ڵ���룬ID16-ID23��0x01-0xff
	
	volatile u8 selfmacid;//Ŀ��ڵ���룬ID8-ID15,0x01-0xff(0x00���ڷ��͹㲥֡)
	
	volatile u8 ack;//��Ӧ��־λ��ID0��0��������֡��1������Ӧ֡
	
}can_id_dataTypeDef;

void CAN1_Init(void);
void answer_master(CanRxMsg *rx_message);
extern bool valve[8];
extern FlagTypedef flag;
#endif
