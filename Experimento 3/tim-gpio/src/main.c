/*
*
* data: 18 de junho de 2020
*
* Exemplo 2: Input Capture e GPIO
*
* Descrição do experimento
*
*/

/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include "stm32f10x_it.h"
#include "shields.h"

void Conf_TIM2_IC(void);
void Conf_NVIC(void);

int main(void)
{
  Conf_GPIO();
  Conf_GPIO_Remap();
  Conf_TIM2_IC();
  Conf_NVIC();

  TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);

  while(1)
  {
    
  }

  return 0;
}

void Conf_TIM2_IC(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_ICInitTypeDef ic;
  ic.TIM_Channel = TIM_Channel_3;
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
  it.NVIC_IRQChannelPreemptionPriority = 0;
  it.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&it);
}

// ----------------------------------------------------------------------------
