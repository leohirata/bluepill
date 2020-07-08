#include "stm32f10x_conf.h"
#include "stm32f10x_it.h"
#include "shields.h"
#include "stdio.h"

void Conf_TIM2(void);
void Conf_ADC(void);
void Conf_NVIC(void);

typedef enum {
  wait_convertion=0,
  data_ready,
  print
}tipo_exemplo_adc;

volatile uint16_t ADC_DADO;
volatile tipo_exemplo_adc estado_exemplo_adc = wait_convertion;

#define a  0.000809
#define b -0.003196

int main(void)
{
  float tensao;

  Conf_GPIO();
  Conf_TIM2();
  Conf_NVIC();

  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);

  Conf_ADC();
  ADC_TempSensorVrefintCmd(ENABLE);

    while(1)
    {
      switch (estado_exemplo_adc) 
      {
      case wait_convertion:
        if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) 
        {
          ADC_DADO = ADC_GetConversionValue (ADC1);
          estado_exemplo_adc = data_ready;
        }
        break;
      case data_ready:
        tensao = a * ADC_DADO + b;
        estado_exemplo_adc = print;
        break;
      case print:
        printf("tensao: %.2f \t ADC: %d\n", tensao, ADC_DADO);
        estado_exemplo_adc = wait_convertion;
        break;
      default:
        break;
      }
    }

    return 0;
}

void Conf_ADC(void) 
{
  RCC_ADCCLKConfig (RCC_PCLK2_Div6);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  ADC_InitTypeDef ADC_St;
  ADC_St.ADC_ContinuousConvMode = DISABLE;
  ADC_St.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_St.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_St.ADC_Mode = ADC_Mode_Independent;
  ADC_St.ADC_NbrOfChannel = 1;
  ADC_St.ADC_ScanConvMode = DISABLE;
  ADC_Init(ADC1, &ADC_St);

  ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_239Cycles5);
  ADC_Cmd (ADC1,ENABLE);

  ADC_ResetCalibration(ADC1); 
  while(ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1); 
  while(ADC_GetCalibrationStatus(ADC1));
}

void Conf_TIM2(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseInitTypeDef timer2;
  timer2.TIM_Prescaler = 7200-1;
  timer2.TIM_Period = 10000-1;
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
