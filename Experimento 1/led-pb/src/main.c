/*
* data: quinta, 28 de maio de 2020
*
* Experimento 1.2: Led e push-buttons
*
* Configurar a GPIO dos pinos do botão e do LED, de modo que o pino do botão
* seja de entrada (input) e do LED de saída (output).
*
* Para o funcionamento da GPIO, deve-se habilitar seus respectivos clocks. 
*
* Use o datasheet e escolha qual porta e pino da GPIO deseja usar. Também use o
* reference manual para saber qual registrador é necessário configurar.
*
* OBS: Faça uma função que detecte a borda de subida no pino do botão. Uma bor-
* da de subida pode ser detectada quando o estado do pino lido for ALTO enquan-
* o estado anterior tenha sido BAIXO. 
*/

// ----------------------------------------------------------------------------
/* ============================ CÓDIGO EXEMPLO ============================= */

#include <stm32f10x_conf.h>
#include <stdio.h>

#define pressionado 1

void Conf_GPIO(void);

int main(void)
{
  Conf_GPIO();

  int estado_botao;

  // GPIO_WriteBit(GPIOA, GPIO_Pin_5, 1);

  while(1)
  {
    estado_botao = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
    if (pressionado == estado_botao)
    {
      GPIO_WriteBit(GPIOA, GPIO_Pin_5, 
        GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5)^1);
      printf("botão pressionado\n");
    }
  }

  return 0;
}

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef portA;
  portA.GPIO_Mode = GPIO_Mode_IPD;
  portA.GPIO_Pin = GPIO_Pin_0;
  portA.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(GPIOA, &portA);

  portA.GPIO_Mode = GPIO_Mode_Out_PP;
  portA.GPIO_Pin = GPIO_Pin_5;

  GPIO_Init(GPIOA, &portA);
}

// int Detecta_Borda(GPIO_TypeDef* porta, uint16_t pino, estado_pb* bot)
// {
//   bot->anterior = bot->atual;
//   bot->atual = GPIO_ReadInputData(porta, pino);

//   return (bot->atual > bot->anterior);
// }

// ----------------------------------------------------------------------------
