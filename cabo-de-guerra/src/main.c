/*
*
* data: sexta, 29 de maio de 2020
*
* Experimento 1.5?: Cabo de guerra
*
* Neste experimento, deverá ser implementado o jogo de cabo de guerra usando
* push-buttons e a placa que contém 7 leds. O jogo deve ser feito para duas
* pessoas.
*
* Faça o jogo da maneira que achar melhor.
*
 */

// ----------------------------------------------------------------------------

#include <stm32f10_conf.h>

#define BOT_RESET GPIO_Pin_0
#define BOT_1     GPIO_Pin_1
#define BOT_2     GPIO_Pin_2
#define ACESO     1
#define APAGADO   0
#define VANTAGEM  2

typedef struct
{
  atual = 0;
  anterior = 0;
} estado_pb;

uint8_t pontos_1 = 0;
uint8_t pontos_2 = 0;

void Conf_GPIO(void);
void Detecta_Borda(GPIO_TypeDef* porta, uint8_t pino, estado_pb* botao);
void Reseta_Jogo(void);

int main(void)
{
  estado_pb botao1, botao2;

  int cabo = 0;

  while(1)
  {
    if (Detecta_Borda(GPIOA, BOT_1, &botao1))
      cabo++;
    if (Detecta_Borda(GPIOA, BOT_2, &botao2))
      cabo--;

    if (cabo == VANTAGEM)
    {
      pontos_1++;

      switch(pontos_1)
      {
        case 1: 
          GPIO_WriteBit(GPIOB, GPIO_Pin_0, ACESO);
          break;
        case 2:
          GPIO_WriteBit(GPIOB, GPIO_Pin_1, ACESO);
          break;
        case 3: 
          GPIO_WriteBit(GPIOB, GPIO_Pin_2, ACESO);
          break;
        case 4:
          GPIO_WriteBit(GPIOB, GPIO_Pin_3, ACESO);
          GPIO_WriteBit(GPIOB, GPIO_Pin_4, APAGADO);
          GPIO_WriteBit(GPIOB, GPIO_Pin_5, APAGADO);
          GPIO_WriteBit(GPIOB, GPIO_Pin_6, APAGADO);
          while(!GPIO_ReadInputDataBit(GPIOA, BOT_RESET));
          Reseta_Jogo();
          break;
        default:
          break;
      }
    }
    else if (cabo == -VANTAGEM)
    {
      pontos_2++;

      switch(pontos_2)
      {
        case 1: 
          GPIO_WriteBit(GPIOB, GPIO_Pin_6 ACESO);
          break;
        case 2:
          GPIO_WriteBit(GPIOB, GPIO_Pin_5, ACESO);
          break;
        case 3: 
          GPIO_WriteBit(GPIOB, GPIO_Pin_4, ACESO);
          break;
        case 4:
          GPIO_WriteBit(GPIOB, GPIO_Pin_3, ACESO);
          GPIO_WriteBit(GPIOB, GPIO_Pin_0, APAGADO);
          GPIO_WriteBit(GPIOB, GPIO_Pin_1, APAGADO);
          GPIO_WriteBit(GPIOB, GPIO_Pin_2, APAGADO);
          while(!GPIO_ReadInputDataBit(GPIOA, BOT_RESET));
          Reseta_Jogo();
          break;
        default:
          break;
      }
    }
  }
} 

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitTypeDef portaA;
  portaA.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  portaA.GPIO_Pin = BOT_RESET | BOT_1 | BOT_2;
  portaA.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &portA);

  GPIO_InitTypeDef portaB;
  portaB.GPIO_Mode = GPIO_Mode_Out_PP;
  portaB.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
                 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
  portaB.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &portB); 
}

void Detecta_Borda(GPIO_TypeDef* porta, uint8_t pino, estado_pb* botao)
{
  botao->anterior = botao->atual;
  botao->atual = GPIO_ReadInputDataBit(porta, pino);

  return botao->atual > botao->anterior;
}

void Reseta_Jogo(void)
{
  GPIO_WriteBit(GPIOB, GPIO_Pin_All, APAGADO);

  uint8_t pontos_1 = 0;
  uint8_t pontos_2 = 0;
}

// ----------------------------------------------------------------------------
