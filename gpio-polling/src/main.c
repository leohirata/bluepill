/*
* data: segunda, 1 de junho de 2020
*
* Experimento 2.2: NVIC e EXTI com GPIO
*
* Neste experimento, aprenderemos como configurar a NVIC para o tratamento das
* interrupções e também a usar as linhas de interrupções da EXTI usando um
* push-button em um pino da GPIO.
*
* Antes de começar, vamos organizar o nosso código criando os arquivos:
* stm32f10x_it.h, stm32f10x_it.c e define.h.
*
* No define.h serão colocadas as definições como struct, enumerate e defines.
*
* Ao configurar alguma linha da EXTI na GPIO, o pino da GPIO irá gerar uma re-
* quisição de interrupção. No stm32f10x_it.c é realizada a rotina da interrup-
* ção, onde no nosso caso, é acendido um led. Terminada a rotina, é necessário
* limpar a flag de interrupção para que ela possa ser requisitada novamente.
* Faça com que ao apertar um botão seja impresso uma frase no semihosting, e
* ao apertar os outros botões leds sejam invertidos.
*
* OBS1: Lembre-se de colocar os arquivos .c na pasta source (src) e os .h na
* pasta include.
*
* OBS2: As linhas EXTI10 até a EXTI15 são tratadas na mesma função.

ANOTAÇÕES:

Explicar que a interrupção da EXTI realiza a mesma função que a Detecta_Borda
 */

/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stm32f10x_conf.h>
#include "shields.h"

void Conf_EXTI(void);

int main(void)
{
  Conf_EXTI();
  Conf_GPIO();

  while(1)
  {
    if (EXTI_GetFlagStatus(EXTI_Line0))
    {
      GPIO_WriteBit(GPIOA, GPIO_Pin_0, 
        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)^1);

      EXTI_ClearFlag(EXTI_Line0);
    }
  }
}

void Conf_EXTI(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);

  EXTI_InitTypeDef portas;
  portas.EXTI_Line = EXTI_Line0;
  portas.EXTI_LineCmd = ENABLE;
  portas.EXTI_Mode = EXTI_Mode_Interrupt;
  portas.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_Init(&portas);
}

// ----------------------------------------------------------------------------
