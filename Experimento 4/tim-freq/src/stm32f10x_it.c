#include <stm32f10x_it.h>
#include <stdio.h>

volatile int frequencia = 0;
int captura, borda_atu, borda_ant = 0;

void TIM2_IRQHandler(void)
{
	borda_atu = TIM_GetCapture3(TIM2);

    if (borda_atu > borda_ant)
    {
      captura = borda_atu - borda_ant;
    }
    else
    {
      captura = 65536 - borda_ant + borda_atu;
    }

    borda_ant = borda_atu;
    frequencia = (72000000/7200)/captura;

    TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
}

void TIM3_IRQHandler(void)
{
  contador_ms++;

  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}
