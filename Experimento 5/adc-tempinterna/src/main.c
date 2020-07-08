#include "stm32f10x_conf.h"
#include "stm32f10x_it.h"
#include "shields.h"
#include "stdio.h"
#include <float.h>

void Conf_TIM2(void);
void Conf_TIM3(void);
void Conf_ADC(void);
// unsigned char HexAscii_Coder (unsigned char stripped_nib);
// void Cria_Pacote_H_Ascii_12 (unsigned char* string, uint16_t data);
void Conf_NVIC(void);

typedef enum {
  wait_convertion=0,
  data_ready,
  print
}tipo_exemplo_adc;

volatile uint16_t ADC_DADO;
volatile tipo_exemplo_adc estado_exemplo_adc = wait_convertion;

#define V_25 1.43
#define Avg_Slope 0.0043

int main(void)
{
  // char aux[50];
//  uint8_t i=0;
  float temperatura;

  Conf_GPIO();
  Conf_TIM2();
  Conf_TIM3();
  Conf_NVIC();

  // Inicia a TIM2
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);//clear na flag para garantir que começa com 0
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);

  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  Conf_ADC();

  LCD_Init();
  LCD_Start();
  LCD_Clear();

  char aux1[20];
  char aux2[20];

  while(1)
  {
    switch (estado_exemplo_adc)
    {
    case wait_convertion:
      if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) {//se acabou a conversão
        ADC_DADO = ADC_GetConversionValue (ADC1);//atribui o valor convertido do ADC1 ao ADC_DADO
        estado_exemplo_adc = data_ready;
      }
      break;
    case data_ready:
      temperatura = (V_25 - ADC_DADO*3.3/4095)/Avg_Slope + 25;
      sprintf(aux1, "temperatura: %.2f", temperatura);
      sprintf(aux2, "ADC: %d", ADC_DADO);
      // sprintf(hexascii_string, "@%X\t%.6f\r\n", ADC_DADO, tensao);//E2 - printa leitura da conversão e a tensão
      //Cria_Pacote_H_Ascii_12 (hexascii_string, ADC_DADO & 0x0FFF);
      // i = 0;
      estado_exemplo_adc = print;
      break;
    case print:
      LCD_Cursor(0, 0);
      LCD_Write(aux1);
      LCD_Cursor(1, 0);
      LCD_Write(aux2);
      // printf("temperatura: %f\n", temperatura);
      // printf("ADC: %d\n", ADC_DADO);
      // if (hexascii_string[i] != '\0') {
      //   if (USART_GetFlagStatus(USART2, USART_FLAG_TXE)) {//se TX está vazio
      //     printf("tensao = %d", (uint16_t)hexascii_string[i]);
      //     i++;
      //   }
      // }
      // printf("\n");
//        else {
        estado_exemplo_adc = wait_convertion;
//        }
      break;
    default:
      break;
    }

    LCD_Cursor(3, 0);
    LCD_Write("teste");
  }

  return 0;
}

void Conf_ADC(void) 
{//configuração do ADC

  RCC_ADCCLKConfig (RCC_PCLK2_Div6);//adc prescaler -> 12MHz
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  ADC_InitTypeDef ADC_St;
  ADC_St.ADC_ContinuousConvMode = DISABLE;
  ADC_St.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_St.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//sem trigger externo
  ADC_St.ADC_Mode = ADC_Mode_Independent;
  ADC_St.ADC_NbrOfChannel = 1;
  ADC_St.ADC_ScanConvMode = DISABLE;//para criar sequencia de escaneamento, mas nesse caso é só 1 canal
  ADC_Init(ADC1, &ADC_St);

  //tempo de amostragem = 12,5 ciclos, Ts = 239,5 --> 12MHz*239,5 = T_aquisição = 252 ciclos --> aprox 21us para armazenar
  ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);

  ADC_TempSensorVrefintCmd(ENABLE);

  ADC_Cmd (ADC1,ENABLE);

  //  ADC calibration (optional, but recommended at power on)
  ADC_ResetCalibration(ADC1); // Reset previous calibration
  while(ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1); // Start new calibration (ADC must be off at that time)
  while(ADC_GetCalibrationStatus(ADC1));
}

// unsigned char HexAscii_Coder (unsigned char stripped_nib) {
//   if ((stripped_nib>=0x00)&(stripped_nib<=0x09))
//     return (stripped_nib + 0x30); // se entre 0x00 e 0x09, soma 0x30
//   else if ((stripped_nib>=0x0A)&(stripped_nib<=0x0F))
//     return (stripped_nib + 0x41 - 0x0A); // se entre 0x0A e 0x0F, soma 0x41
//   else
//     return (0x00); // retorna NULL caso contrário
// }

// void Cria_Pacote_H_Ascii_12 (unsigned char* string, uint16_t data){
//   string [0] = '@';
//   string [1] = HexAscii_Coder(data>>8);
//   string [2] = HexAscii_Coder((data>>4) & 0x000F);
//   string [3] = HexAscii_Coder(data & 0x000F);
//   string [4] = '\r';
//   string [5] = '\n';
//   string [6] = '\0';
// }

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
