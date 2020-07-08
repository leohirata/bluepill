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

void Conf_TIM2(void);
void Conf_TIM2_IC(void);
void Conf_NVIC(void);

int main(void)
{
  Conf_GPIO();
  Conf_GPIO_Remap();
  Conf_TIM2();
  Conf_TIM2_IC();
  Conf_NVIC();

  TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  //uint16_t digitos[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90}; // ânodo comum
  uint8_t digitos[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // cátodo comum

  GPIO_Write(GPIOA, digitos[indice1]);

  while(1)
  {
    if (1 == reseta)
    {
      reseta = 0;
      GPIO_WriteBit(GPIOB, GPIO_Pin_12, APAGADO);
      GPIO_WriteBit(GPIOB, GPIO_Pin_13, APAGADO);
      GPIO_WriteBit(GPIOB, GPIO_Pin_14, APAGADO);
    }

    if (0 == display)
      GPIO_Write(GPIOA, digitos[indice1]);
    else if (1 == display)
      GPIO_Write(GPIOA, digitos[indice2]);
    else
      GPIO_Write(GPIOA, digitos[indice3]);
 
  }

  return 0;
}

void Conf_TIM2(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseInitTypeDef timer2;
  timer2.TIM_Prescaler = 1200-1;
  timer2.TIM_Period = 1000-1;
  timer2.TIM_CounterMode =  TIM_CounterMode_Up;
  timer2.TIM_ClockDivision = 0;
  timer2.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &timer2);
}

void Conf_TIM2_IC(void)
{
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
