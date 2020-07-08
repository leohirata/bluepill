#include "shields.h"

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitTypeDef portaA;
  portaA.GPIO_Mode = GPIO_Mode_IPD;
  portaA.GPIO_Pin = BOT_RESET | BOT_1 | BOT_2;
  portaA.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &portaA);

  GPIO_InitTypeDef portaB;
  portaB.GPIO_Mode = GPIO_Mode_Out_PP;
  portaB.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4
                 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  portaB.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &portaB);
}
