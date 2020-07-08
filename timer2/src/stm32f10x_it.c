#include "stm32f10x_it.h"

int i = 0;

void TIM2_IRQHandler(void){
	//Inverte o LED1
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)^1 );
	// Zera o sinal de requisição da interrupção
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	printf("i = %d\n", i++);

	//GPIOC->BSRR = (1<<13);
}
