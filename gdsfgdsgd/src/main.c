#include <stm32f4xx.h>
#include <stm32f407xx.h>
#include <stm32f4x_conf.h>

int main(void)
{
//	HAL_GPIO_Init();
	GPIO_WriteBit(GPIOA, GPIO_PIN_0, 1);
	return 0;
}
