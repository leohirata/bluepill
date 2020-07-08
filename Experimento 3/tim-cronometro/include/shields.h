#ifndef __shields
#define __shields

#include <stm32f10x_conf.h>

#define APAGADO    0
#define ACESO   1

#define BOT_Press 1
#define BOT_Solto 0

void Conf_GPIO(void);
void Conf_GPIO_Remap(void);

#endif
