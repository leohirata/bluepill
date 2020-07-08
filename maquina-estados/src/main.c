/*
* data: segunda, 1 de junho de 2020
*
* Experimento 2.3: Maquina de estados
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
#include "stm32f10x_it.h"
#include "shields.h"

void Conf_EXTI(void);
void Conf_NVIC(void);

typedef enum
{

} estado;

int main(void)
{  
  SysTick_Init();
  Conf_NVIC();
  Conf_EXTI();
  Conf_GPIO();
  
  while(1)
  {

  }

}

void Conf_EXTI(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15);
  
  EXTI_InitTypeDef portas;
  portas.EXTI_Line = EXTI_Line0 | EXTI_Line12 | EXTI_Line15;
  portas.EXTI_LineCmd = ENABLE;
  portas.EXTI_Mode = EXTI_Mode_Interrupt;
  portas.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_Init(&portas);
}

void Conf_NVIC(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  NVIC_InitTypeDef it;
  it.NVIC_IRQChannel = EXTI0_IRQn;
  it.NVIC_IRQChannelCmd = ENABLE;
  it.NVIC_IRQChannelPreemptionPriority = 1;
  it.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&it);

  it.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_Init(&it);
}

// ----------------------------------------------------------------------------
