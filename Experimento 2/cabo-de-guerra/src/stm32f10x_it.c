#include "stm32f10x_it.h"

volatile int cabo = 0;

void EXTI0_IRQHandler(void)
{
  cabo++;

  EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler (void)
{
  cabo--;

  EXTI_ClearITPendingBit(EXTI_Line1);
}
