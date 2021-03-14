#ifndef _MAIN_H
#define _MAIN_H

#include "stdbool.h"
#include "stm32f10x.h"
#include "can1.h"
#include "tim3.h"
#include "delay.h"

void Valve_Configuration(void);
void LED_Init(void);
void LED_Show(void);
void BEEP_Init(void);
void BEEP_Show(u8 i);

#define BEEP_ON GPIO_SetBits(GPIOB, GPIO_Pin_15);
#define BEEP_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_15);
#endif
