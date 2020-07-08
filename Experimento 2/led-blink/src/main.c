/*

* data: quarta, 27 de maio de 2020
*
* Experimento 1: GPIO

Registradores de configuração (32 bits) - página
GPIOx_ModeR: entrada analógica, entrada flutuante, entrada com resistor de pull-down para
não ficar flutuando, entrada com resistor de pull-up para não ficar flutuando, saída open drain
(0 ou flutuante, pois quando o gate é high, o dreno e o source são curto circuitados, gerando 0
na saída, e se o gate for low, a conexão entre o dreno e o source abre e a saída flutua),
saída push-pull (contém 2 mosfets, em que se o gate for high, sai 1, e se o gate for low, sai 0),
alternate function open drain ou push pull (é usado por outros periféricos como timers, etc).

GPIOx_OTYPER:
GPIOx_OSPEEDR:
GPIOx_PUPDR:

Registradores de dados (32 bits)
GPIOx_IDR:
GPIOx_ODR:

Registrador de set/reset (32 bits)
GPIOx_BSRR:

Locking register (32 bits)
GPIOx_LCKR: faz com que as configurações sejam mantidas até que haja um reset no MCU ou no
periférico

Alternate function registers (32 bits)
GPIOx_AFRH:
GPIOx_AFRL:

A aquisição de dados nos pinos é feita a cada ciclo de clock AHB.

Ao usar os clocks externos HSE ou LSE, apenas o pino de entrada é reservado para estes clocks,
os outros pinos podem usar os OSC_OUT e o OSC32_OUT

O campo SPEED não afeta o clock, mas afeta a potência consumida pelo pino. Usar a menor
frequência possível.
*/

// ----------------------------------------------------------------------------
/* ============================ CÓDIGO EXEMPLO ============================= */

#include <stdio.h>
#include <stm32f10x_conf.h>

void delay(void);
void Conf_GPIO(void);

int main(void)
{
	Conf_GPIO();

	while (1)
	{
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)^1);
		delay();
	}

	return 0;
}

void Conf_GPIO(void)
{
//	Configurando o clock da GPIOx
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

//	Configurando o pino 13 da GPIOC
	GPIO_InitTypeDef portC;
	portC.GPIO_Mode = GPIO_Mode_Out_PP;
	portC.GPIO_Pin = GPIO_Pin_13;
	portC.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(GPIOC, &portC);
}

void delay(void)
{
//	Criando um delay bloqueante (que interrompe o processamento das outras instruções)
	volatile unsigned int i;

	for (i = 0; i < 2000000; i++);
}


// ----------------------------------------------------------------------------
