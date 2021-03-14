#ifndef _TIM3_H
#define _TIM3_H

#include "stm32f10x_tim.h"
#include "stm32f10x.h"
#include "can1.h"

void TIM3_Init(void);
void TIM3_IRQHandler(void);
void Defense_answer_master(void);

#endif


