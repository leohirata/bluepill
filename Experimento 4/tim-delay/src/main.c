/*
*
* data: 20 de junho de 2020
*
* Experimento x: xxxx xxxx
*
* Descrição do experimento
*
*/

/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include "shields.h"
#include "stm32f10x_it.h"

void Conf_TIM3(void);
void Conf_NVIC(void);
void TIM3_Delay(uint32_t tempo);

int main(void)
{
  Conf_GPIO();
  Conf_TIM3();
  Conf_NVIC();

  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  while(1)
  {
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, 
      GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)^1);
  
    TIM3_Delay(500);
  }

  return 0;
}

void Conf_TIM3(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  
  TIM_TimeBaseInitTypeDef timer3;
  timer3.TIM_Prescaler = 72-1;
  timer3.TIM_Period = 1000-1;
  timer3.TIM_CounterMode =  TIM_CounterMode_Up;
  timer3.TIM_ClockDivision = 0;
  timer3.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM3, &timer3);
}

void Conf_NVIC(void)
{
  NVIC_InitTypeDef it;
  it.NVIC_IRQChannel = TIM3_IRQn;
  it.NVIC_IRQChannelCmd = ENABLE;
  it.NVIC_IRQChannelPreemptionPriority = 0;
  it.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&it);
}

void TIM3_Delay(uint32_t tempo)
{
  TIM_Cmd(TIM3, ENABLE);

  while(tempo != contador_ms);

  contador_ms = 0;

  TIM_Cmd(TIM3, DISABLE);
}

// ----------------------------------------------------------------------------
