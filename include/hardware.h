#ifndef __HARDWARE_HEAD
#define __HARDWARE_HEAD

#include "stm32f4xx.h"
#ifndef __STM32F4xx_H
// discards warning related to supposed non-direct use of stm32 header
#endif

#define LED_PIN 5 // pin 5 is at bit 5, just 1 bit for each output
#define EXT_LED_PIN 8
#define EXT_LED_PINB 5

/* Data that initializes the stack pointer */
#define SRAM1_START (0x20000000U)
#define SRAM1_SIZE (112U * 1024U)
#define SRAM1_END (SRAM1_START + SRAM1_SIZE)
#define STACK_POINTER_INIT_ADDRESS (SRAM1_END) // start at end

#endif
