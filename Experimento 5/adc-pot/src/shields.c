#include "shields.h"

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef portaA;
  portaA.GPIO_Mode = GPIO_Mode_AIN;
  portaA.GPIO_Speed = GPIO_Speed_2MHz;
  portaA.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOA, &portaA);
}
