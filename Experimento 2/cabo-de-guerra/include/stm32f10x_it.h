#ifndef __stm32f10x_it
#define __stm32f10x_it

#include "stm32f10x_conf.h"

extern volatile int cabo;

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);

#endif