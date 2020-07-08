#ifndef __stm32f10x_it
#define __stm32f10x_it

#include "stm32f10x_conf.h"

extern volatile uint8_t troca_digito;
extern volatile uint8_t reseta;
extern volatile uint8_t display;
extern volatile uint8_t indice1;
extern volatile uint8_t indice2;
extern volatile uint8_t indice3;

void TIM2_IRQHandler(void);

typedef enum
{
  start = 0,
  stop,
  restart
} estados;

#endif
