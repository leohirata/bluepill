#include "stm32f10x_it.h"
#include <stdio.h>

void TIM2_IRQHandler(void)
{
  // Qualquer um destes dois comandos abaixo inicia a aquisição
  ADC_Cmd(ADC1, ENABLE);
  //ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  //a cada 1s o ADC começa a converter
}

void TIM3_IRQHandler(void)
{
  contador_ms++;

  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

