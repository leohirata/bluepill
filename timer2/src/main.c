/*
 * This file is part of the ÂµOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stm32f10x_conf.h>
#include "stm32f10x_it.h"

// ----------------------------------------------------------------------------
//
// STM32F1 led blink sample (trace via DEBUG).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// To demonstrate POSIX retargetting, reroute the STDOUT and STDERR to the
// trace device and display messages on both of them.
//
// Then demonstrates how to blink a led with 1 Hz, using a
// continuous loop and SysTick delays.
//
// On DEBUG, the uptime in seconds is also displayed on the trace device.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//
// The external clock frequency is specified as a preprocessor definition
// passed to the compiler via a command line option (see the 'C/C++ General' ->
// 'Paths and Symbols' -> the 'Symbols' tab, if you want to change it).
// The value selected during project creation was HSE_VALUE=72000000.
//
// Note: The default clock settings take the user defined HSE_VALUE and try
// to reach the maximum possible system clock. For the default 8 MHz input
// the result is guaranteed, but for other values it might not be possible,
// so please adjust the PLL settings in system/src/cmsis/system_stm32f10x.c
//

void Conf_NVIC (void);
void Conf_TIM2 (void);

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	Conf_TIM2();
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//Passo 3
	Conf_NVIC();
	TIM_Cmd(TIM2, ENABLE);

	GPIO_InitTypeDef portC;
	portC.GPIO_Mode = GPIO_Mode_Out_PP;
	portC.GPIO_Pin = GPIO_Pin_13;
	portC.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &portC);

	while(1)
	{

	}

  return 0;
}

void Conf_TIM2 (void)
{	//Passo 2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef TIM2_Olair;
	TIM2_Olair.TIM_Prescaler = 7199;
	TIM2_Olair.TIM_CounterMode = TIM_CounterMode_Up;
	TIM2_Olair.TIM_Period = 4999;
	TIM2_Olair.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM2, &TIM2_Olair);
}

void Conf_NVIC (void) {
	NVIC_InitTypeDef nVICKY;
	//NVIC_PriorityGroupConfig (NVIC_PriorityGroup_4); // 1 bits para sub-prioridade 3 bits para prioridade
	//Ativa a EXTI0_IRQn
	nVICKY.NVIC_IRQChannel = TIM2_IRQn;
	nVICKY.NVIC_IRQChannelCmd = ENABLE;
	nVICKY.NVIC_IRQChannelPreemptionPriority = 1; // Maior prioridade, apenas menor que a do Systick
	nVICKY.NVIC_IRQChannelSubPriority = 0; // Maior sub-prioridade possível
	NVIC_Init(&nVICKY);
}
// ----------------------------------------------------------------------------
