#ifndef __shields
#define __shields

#include <stm32f10x_conf.h>

#define BOT_RESET GPIO_Pin_0
#define BOT_1     GPIO_Pin_1
#define BOT_2     GPIO_Pin_2

void Conf_GPIO(void);

#endif
