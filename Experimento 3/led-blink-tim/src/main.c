/*
*
* data: 17 de junho de 2020
*
* Exemplo 1: TIM e LED
*
* Descrição do experimento
*
*/

/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include "stm32f10x_it.h"
#include "shields.h"

void Conf_TIM2(void);
void Conf_NVIC(void);

int main(void)
{

  Conf_GPIO();
  Conf_TIM2();
  Conf_NVIC();

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);

  while(1)
  {
    
  }

  return 0;
}

void Conf_TIM2(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  
  TIM_TimeBaseInitTypeDef timer2;
  timer2.TIM_Prescaler = 7200-1;
  timer2.TIM_Period = 5000-1;
  timer2.TIM_CounterMode =  TIM_CounterMode_Up;
  timer2.TIM_ClockDivision = 0;
  timer2.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &timer2);
}

void Conf_NVIC(void)
{
  NVIC_InitTypeDef it;
  it.NVIC_IRQChannel = TIM2_IRQn;
  it.NVIC_IRQChannelCmd = ENABLE;
  it.NVIC_IRQChannelPreemptionPriority = 0;
  it.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&it);
}

// ----------------------------------------------------------------------------
