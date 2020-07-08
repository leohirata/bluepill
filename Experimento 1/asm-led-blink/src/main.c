;******************** (C) COPYRIGHT 2018 IoTality ********************
;* File Name          : LED.s
;* Author             : Gopal
;* Date               : 07-Feb-2018
;* Description        : A simple code to blink LEDs on STM32F4 discovery board
;*                      - The functions are called from startup code
;*                      - Initialization carried out for GPIO-D pins PD12 to PD15 (connected to LEDs)
;*                      - Blink interval delay implemented in software
;*******************************************************************************

; ******* Constants *******
;Delay interval
;The delay loop takes 313 nsec to execute at 16MHz
;Time delay = DELAY_INTERVAL * 313 nsec
;Overheads are ignored

DELAY_INTERVAL  EQU 0x186004

; ******* Register definitions *******
;GPIOC_CRL ; 0 a 7
;GPIOC_CRH   equ 0xCC2CCCCC ; 8 a 15; configurando o pino 13 da GPIOC como saída push-pull

;GPIOC_IDR registrador de dados de entrada
;GPIOC_ODR registrador de dados de saída
;GPIOC_BSRR  equ 0x00002000 ; setando a saída do LED
;GPIOC_BRR   equ 0x00000000 ; 

RCC_CR      equ 0x40021000 ; clock control register
RCC_CFGR    equ 0x40021004 ; clock configuration register
RCC_CIR     equ 0x4002100C ; clock interrupt register
RCC_APB2RSTR equ 0x40021018 ; APB2 peripheral reset register
RCC_APB1RSTR equ 0x40021028 ; APB1 peripheral reset register
RCC_AHBENR   equ 0x4002103C ; AHB peripheral clock enable register
RCC_APB2ENR  equ 0x40021054 ; APB2 peripheral clock enable register
RCC_APB1ENR  equ 0x40021070 ; APB1 peripheral clock enable register

GPIOC_CRL   equ 0x40011000 ; port configuration register low
GPIOC_CRH   equ 0x40011004 ; port configuration register high
GPIOC_IDR   equ 0x4001100C ; port input data register
GPIOC_ODR   equ 0x40011018 ; port output data register
GPIOC_BSRR  equ 0x40011028 ; port bit set/reset register
GPIOC_BRR   equ 0x4001103C ; port bit reset register
; **************************
    
; ******* Function SystemInit *******
; * Enables GPIO clock 
; * Configures GPIOC Pin 13 as:
; ** Output
; ** Push-pull (Default configuration)
; ** 2M Hz speed
; **************************

SystemInit FUNCTION

  ; Habilita o clock APB2 da GPIOC
  LDR   R1, =RCC_APB2ENR  ;Pseudo-load address in R1
  LDR   R0, [R1]      ;Copy contents at address in R1 to R0
  ORR.W   R0, #0x08     ;Bitwise OR entire word in R0, result in R0
  STR   R0, [R1]      ;Store R0 contents to address in R1

  ; Set mode as output
  LDR   R1, =GPIOD_MODER  ;Two bits per pin so bits 24 to 31 control pins 12 to 15
  LDR   R0, [R1]      
  ORR.W   R0, #0x55000000   ;Mode bits set to '01' makes the pin mode as output
  AND.W R0, #0x55FFFFFF   ;OR and AND both operations reqd for 2 bits
  STR   R0, [R1]

  ; Set type as push-pull (Default)
  LDR   R1, =GPIOD_OTYPER ;Type bit '0' configures pin for push-pull
  LDR   R0, [R1]
  AND.W   R0, #0xFFFF0FFF 
  STR   R0, [R1]
  
  ; Set Speed slow
  LDR   R1, =GPIOD_OSPEEDR  ;Two bits per pin so bits 24 to 31 control pins 12 to 15
  LDR   R0, [R1]
  AND.W   R0, #0x00FFFFFF   ;Speed bits set to '00' configures pin for slow speed
  STR   R0, [R1]  
  
  ; Set pull-up
  LDR   R1, =GPIOD_PUPDR  ;Two bits per pin so bits 24 to 31 control pins 12 to 15
  LDR   R0, [R1]
  AND.W R0, #0x00FFFFFF   ;Clear bits to disable pullup/pulldown
  STR   R0, [R1]

  BX    LR          ;Return from function
  
  ENDFUNC
  

; ******* Function SystemInit *******
; * Called from startup code
; * Calls - None
; * Infinite loop, never returns

; * Turns on / off GPIO-D Pins 12 to 15
; * Implements blinking delay 
; ** A single loop of delay uses total 6 clock cycles
; ** One cycle each for CBZ and SUBS instructions
; ** 3 cycles for B instruction
; ** B instruction takes 1+p cycles where p=pipeline refil cycles
; **************************

__main FUNCTION
  
turnON
  ; Set output high
  LDR   R1, =GPIOD_ODR
  LDR   R0, [R1]
  ORR.W   R0, #0xF000
  STR   R0, [R1]

  LDR   R2, =DELAY_INTERVAL
  
delay1
  CBZ   R2, turnOFF
  SUBS  R2, R2, #1
  B   delay1
  
turnOFF
  ; Set output low
  LDR   R1, =GPIOD_ODR
  LDR   R0, [R1]
  AND.W R0, #0xFFFF0FFF
  STR   R0, [R1]  
  
  LDR   R2,=DELAY_INTERVAL
delay2
  CBZ   R2, delayDone
  SUBS  R2, R2, #1
  B   delay2

delayDone
  B   turnON

  ENDFUNC
  
  
  END