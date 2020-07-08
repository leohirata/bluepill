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

void Conf_GPIO_Remap(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

  GPIO_InitTypeDef portaB;
  portaB.GPIO_Mode = GPIO_Mode_IPD;
  portaB.GPIO_Pin = GPIO_Pin_10;
  portaB.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &portaB);

  GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
}
