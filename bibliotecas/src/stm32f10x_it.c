#include "stm32f10x_it.h"
#include <stdio.h>

void EXTI0_IRQHandler(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_0,
	  GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0)^1);

  EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI15_10_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line12))
  {
    GPIO_WriteBit(GPIOA, GPIO_Pin_1,
      GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1)^1);

    EXTI_ClearITPendingBit(EXTI_Line12);
  }
  else if (EXTI_GetITStatus(EXTI_Line15))
  {
    GPIO_WriteBit(GPIOA, GPIO_Pin_2,
      GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2)^1);

    EXTI_ClearITPendingBit(EXTI_Line15);
  }
}
