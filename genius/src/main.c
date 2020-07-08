/*
*
* data: sexta, 29 de maio de 2020
*
* Descontinuado. Jogo com implementação complexa.
 */

// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include <stdio.h>
#include <time.h>

typedef enum
{
  vermelho = 0,
  azul,
  verde,
  amarelo,
  branco
} cores;

int main(void)
{
  uint8_t cor;

  while(1)
  { 
    srand(time(0));
  
    uint8_t sequencia[100] = {0};
    uint16_t i = 0;

    while(cores)
    {
      cor = rand(10) % 5;

      switch(cor)
      {
        case vermelho:
          sequencia[i] = vermelho;
          GPIO_WriteBit(GPIOA, GPIO_Pin_0 , ACESO);
          delay(500);
          GPIO_WriteBit(GPIOA, GPIO_Pin_0, APAGADO);
          break;
        case azul:
          sequencia[i] = azul;
          GPIO_WriteBit(GPIOA, GPIO_Pin_1, ACESO);
          delay(500);
          GPIO_WriteBit(GPIOA, GPIO_Pin_1, APAGADO);
          break;
        case verde:
          sequencia[i] = verde;
          GPIO_WriteBit(GPIOA, GPIO_Pin_2, ACESO);
          delay(500);
          GPIO_WriteBit(GPIOA, GPIO_Pin_2, APAGADO);
          break;
        case amarelo:
          sequencia[i] = amarelo;
          GPIO_WriteBit(GPIOA, GPIO_Pin_3, ACESO);
          delay(500);
          GPIO_WriteBit(GPIOA, GPIO_Pin_3, APAGADO);
          break;
        case branco:
          sequencia[i] = branco;
          GPIO_WriteBit(GPIOA, GPIO_Pin_4, ACESO);
          delay(500);
          GPIO_WriteBit(GPIOA, GPIO_Pin_4, APAGADO);
          break;
        default:
          break;
      }
      cores--;
      i++;

    }

    
  }
}
// ----------------------------------------------------------------------------
