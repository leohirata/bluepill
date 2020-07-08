#include "shields.h"

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef portaA;
  portaA.GPIO_Mode = GPIO_Mode_Out_PP;
  portaA.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
                 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
  portaA.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &portaA);
}
