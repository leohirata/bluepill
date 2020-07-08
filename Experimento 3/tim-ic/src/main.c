/*
*
* data: xx, xx de xxx de xxxx
*
* Experimento x: xxxx xxxx
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

void Conf_TIM2_IC(void)
{
  TIM_ICInitTypeDef ic;
  ic.TIM_Channel = TIM_Channel_1;
  ic.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  ic.TIM_ICPolarity = TIM_ICPolarity_Rising;
  ic.TIM_ICFilter = 0;
  ic.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInit(TIM2, &ic);
}

void Conf_NVIC(void)
{
  NVIC_InitTypeDef it;
  it.NVIC_IRQChannel = TIM2_IRQn;
  it.NVIC_IRQChannelCmd = ENABLE;
  it.NVIC_IRQChannelPreemptionPriority = 1;
  it.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&it);
}

// ----------------------------------------------------------------------------
