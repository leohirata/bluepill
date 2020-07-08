#include "shields.h"

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef portaC;
  portaC.GPIO_Mode = GPIO_Mode_Out_PP;
  portaC.GPIO_Pin = GPIO_Pin_13;
  portaC.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &portaC);
}
