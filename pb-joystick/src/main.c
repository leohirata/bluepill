/*
* data: quinta, 28 de maio de 2020
*
* Experimento 1.3: Joystick com push-buttons
*
* Neste experimento, faremos um joystick usando 5 push-buttons. Como no experi-
* mento anterior, configure os pinos e a(s) porta(s) GPIO que deseja usar, e
* então faça uma função que detecte uma borda de subida nos pinos de entrada,
* ou seja, o estado atual do pino é ALTO e o estado anterior é BAIXO. 
*
* Ao pressionar algum botão do joystick, uma impressão respectiva ao botão
* pressionado irá aparecer no semihosting.
*
* OBS: Habilite o semihosting na criação do projeto.
*/

// ----------------------------------------------------------------------------
/* ============================ CÓDIGO EXEMPLO ============================= */

#include <stdio.h>
#include <stm32f10x_conf.h>

typedef struct
{
  uint8_t atual;
  uint8_t anterior;
} estado_pb;

typedef enum 
{
  erro = -1,
  esquerdo = 0,
  direito,
  cima,
  baixo,
  centro
} estado;

void Conf_GPIO(void);
int Estado_Botao(estado_pb* bot_esquerdo, estado_pb* bot_direito, 
                estado_pb* bot_cima, estado_pb* bot_baixo, 
                estado_pb* bot_centro);

int main(void)
{

  Conf_GPIO();

  estado_pb bot_esquerdo, bot_direito, bot_cima, bot_baixo, bot_centro;
  estado joystick;

  bot_esquerdo.anterior = 0;
  bot_esquerdo.atual = 0;
  bot_direito.anterior = 0;
  bot_direito.atual = 0;
  bot_cima.anterior = 0;
  bot_cima.atual = 0;
  bot_baixo.anterior = 0;
  bot_baixo.atual = 0;  
  bot_centro.anterior = 0;
  bot_centro.atual = 0;


	while(1)
	{
    joystick = Estado_Botao(&bot_esquerdo, &bot_direito, &bot_cima,
                            &bot_baixo, &bot_centro);
      switch (joystick)
      {
        case erro:
          break;
        case esquerdo:
          printf("Esquerda\n");
          break;
        case direito:
          printf("Direita\n");
          break;
        case cima:
          printf("Cima\n");
          break;
        case baixo:
          printf("Baixo\n");
          break;
        case centro:
          printf("Centro\n");
          break; 
      }
    }

	return 0;
}

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef portaA;
  portaA.GPIO_Mode = GPIO_Mode_IPD;
  portaA.GPIO_Pin = GPIO_Pin_0
                 | GPIO_Pin_1
                 | GPIO_Pin_2
                 | GPIO_Pin_3
                 | GPIO_Pin_4;
  portaA.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &portaA);
}

int Estado_Botao(estado_pb* bot_esquerdo, estado_pb* bot_direito, 
                estado_pb* bot_cima, estado_pb* bot_baixo, 
                estado_pb* bot_centro)
{
  bot_esquerdo->atual = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
  bot_direito->atual = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
  bot_cima->atual = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
  bot_baixo->atual = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3);
  bot_centro->atual = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);

  if (bot_esquerdo->atual > bot_esquerdo->anterior)
  {
    bot_esquerdo->anterior = bot_esquerdo->atual;
    return 0;
  }
  else if (bot_direito->atual > bot_direito->anterior)
  {
    bot_direito->anterior = bot_direito->atual;
    return 1;
  }
  else if (bot_cima->atual > bot_cima->anterior)
  {
    bot_cima->anterior = bot_cima->atual;
    return 2;
  }
  else if (bot_baixo->atual > bot_baixo->anterior)
  {
    bot_baixo->anterior = bot_baixo->atual;
    return 3;
  }
  else if (bot_centro->atual > bot_centro->anterior)
  {
    bot_centro->anterior = bot_centro->atual;
    return 4;
  }
  else
  {
	bot_esquerdo->anterior = bot_esquerdo->atual;
	bot_direito->anterior = bot_direito->atual;
	bot_cima->anterior = bot_cima->atual;
	bot_baixo->anterior = bot_baixo->atual;
	bot_centro->anterior = bot_centro->atual;
	return -1;
  }
}

// int Detecta_Borda(GPIO_TypeDef* porta, uint16_t pino, estado_pb* bot)
// {
//   bot->anterior = bot->atual;
//   bot->atual = GPIO_ReadInputData(porta, pino);

//   return (bot->atual > bot->anterior);
// }

// ----------------------------------------------------------------------------
