#include <stm32f10x_it.h>

void TIM2_IRQHandler(void)
{
  GPIO_WriteBit(GPIOB, GPIO_Pin_0, 
    GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0)^1);

  TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
}

