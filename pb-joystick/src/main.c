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

/* ============================ CÓDIGO EXEMPLO ============================= */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stm32f10x_conf.h>

void Conf_GPIO(void);

typedef struct
{
  uint8_t atual;
  uint8_t anterior = 0;
} estado_pb;

typedef enum 
{
  esquerdo = 0,
  direito,
  cima,
  baixo,
  centro
} estado;


int main(void)
{

  Conf_GPIO();

  estado_pb* botao;
  estado joystick;

	while(1)
	{
    joystick = Estado_Botao;
      switch (joystick)
      {
        case esquerdo:
          printf("Esquerda\n");
        case direito:
          printf("Direita\n");
        case cima:
          printf("Cima\n");
        case baixo:
          printf("Baixo\n");
        case centro:
          printf("Centro\n");
        default:
          break;  
      }
    }

	return 0;
}

void Conf_GPIO(void)
{
  RCC_APB2Periph(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef portA;
  portA.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  portA.GPIO_Pin = GPIO_Pin_0
                 | GPIO_Pin_1
                 | GPIO_Pin_2
                 | GPIO_Pin_3
                 | GPIO_Pin_4;
  portA.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &portA);
}

int Estado_Botao(void)
{
  estado_pb esquerdo, direito, cima, baixo, centro;

  esquerdo.atual = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
  direito.atual = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1);
  cima.atual = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2);
  baixo.atual = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3);
  centro.atual = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4);

  if (esquerdo->atual > esquerdo->anterior)
  {
    esquerdo->anterior = esquerdo->atual;
    return 0;
  }
  else if (direito->atual > direito->anterior)
  {
    direito->anterior = direito->atual;
    return 1;
  }
  else if (cima->atual > cima->anterior)
  {
    cima->anterior = cima->atual;
    return 2;
  }
  else if (baixo->atual > baixo->anterior)
  {
    baixo->anterior = baixo->atual;
    return 3;
  }
  else if (centro->atual > centro->anterior)
  {
    centro->anterior = centro->atual;
    return 4;
  }
}

// int Detecta_Borda(GPIO_TypeDef* porta, uint16_t pino, estado_pb* bot)
// {
//   bot->anterior = bot->atual;
//   bot->atual = GPIO_ReadInputData(porta, pino);

//   return (bot->atual > bot->anterior);
// }

// ----------------------------------------------------------------------------