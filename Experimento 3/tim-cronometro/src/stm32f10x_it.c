#include <stm32f10x_it.h>
#include "shields.h"

volatile uint8_t troca_digito = 0;
volatile uint8_t reseta = 0;
volatile uint8_t display = 0;
volatile uint8_t indice1 = 0;
volatile uint8_t indice2 = 0;
volatile uint8_t indice3 = 0;
uint32_t count = 0;
estados pb = 0;

void TIM2_IRQHandler(void)
{
  if (TIM_GetFlagStatus(TIM2, TIM_IT_CC3))
  {
    switch (pb)
    {
      case start:
        TIM_Cmd(TIM2, ENABLE);
        pb = stop;
        break;
      case stop:
        pb = restart;
        break;
      case restart:
    	TIM_Cmd(TIM2, DISABLE);
        reseta = 1;
        indice1 = 0;
        indice2 = 0;
        indice3 = 0;
        pb = start;
        break;
      default:
        break;
    }

    TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
  }
  else
  { 
  	if (pb == restart)
  	{
      GPIO_WriteBit(GPIOB, GPIO_Pin_12, APAGADO);
      GPIO_WriteBit(GPIOB, GPIO_Pin_13, ACESO);
      GPIO_WriteBit(GPIOB, GPIO_Pin_14, APAGADO);
  	}
  	else
  	{
        if (count == 60)
        {
          count = 0;
          indice1++;

    	    if (10 == indice1)
    	    {
    	      indice1 = 0;
    	      indice2++;

    	      if (6 == indice2)
    	      {
    	        indice2 = 0;
              indice3++;

              if (10 == indice3)
              {
                indice3 = 0;
              }
    	      }
          }
        }
        else
        {
          count++;
        }
  	}

  switch (display)
  {
    case 0:
      GPIO_WriteBit(GPIOB, GPIO_Pin_12, APAGADO);
      GPIO_WriteBit(GPIOB, GPIO_Pin_13, ACESO);
      GPIO_WriteBit(GPIOB, GPIO_Pin_14, APAGADO);
      display = 1;
      break;
    case 1:
      GPIO_WriteBit(GPIOB, GPIO_Pin_12, APAGADO);
      GPIO_WriteBit(GPIOB, GPIO_Pin_13, APAGADO);
      GPIO_WriteBit(GPIOB, GPIO_Pin_14, ACESO);
      display = 2;
      break;
    case 2:
      GPIO_WriteBit(GPIOB, GPIO_Pin_12, ACESO);
      GPIO_WriteBit(GPIOB, GPIO_Pin_13, APAGADO);
      GPIO_WriteBit(GPIOB, GPIO_Pin_14, APAGADO);
      display = 0;
      break;
    default:
      break;
  }

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  }
}

