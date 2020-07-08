#include <stm32f10x_it.h>

volatile int conta_borda = 0;

void TIM2_IRQHandler(void)
{
  conta_borda++;

  TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
}

void TIM3_IRQHandler(void)
{
  contador_ms++;

  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

