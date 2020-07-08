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
#include "lcd1602.h"
#include <stdio.h>

void Conf_TIM2_IC(void);
void Conf_TIM3(void);
void Conf_NVIC(void);

int main(void)
{
  Conf_GPIO();
  Conf_GPIO_Remap();
  Conf_TIM2_IC();
  Conf_TIM3();
  Conf_NVIC();

  TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  LCD_Init();
  LCD_Start();
  LCD_Clear();

  char teste[20] = "Leonardo";
  // int i = 0;
  char aux[20];

  while(1)
  {
	  LCD_Cursor(2, 0);
	  sprintf(aux, "bordas = %d", conta_borda);
	  LCD_Write(aux);
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
  it.NVIC_IRQChannel = TIM2_IRQn;
  it.NVIC_IRQChannelCmd = ENABLE;
  it.NVIC_IRQChannelPreemptionPriority = 0;
  it.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&it);

  it.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_Init(&it);
}

// ----------------------------------------------------------------------------
