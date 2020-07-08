#include "stm32f10x_it.h"
#include <stdio.h>

void TIM2_IRQHandler(void)
{
  ADC_Cmd(ADC1, ENABLE);
  //ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
