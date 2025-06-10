#pragma once

#include <stdint.h>
#include "stm32f4xx.h"

/* Data that initializes the stack pointer */
#define SRAM1_START (0x20000000U)
#define SRAM1_SIZE (112U * 1024U)
#define SRAM1_END (SRAM1_START + SRAM1_SIZE)
#define STACK_POINTER_INIT_ADDRESS (SRAM1_END) // start at end

/* 
* MODER configuration:
* 0b00: Input (reset state)
* 0b01: Generate Purpose OUTPUT mode
* 0b10: Alternate function mode
* 0b11: Analog mode
*/
#define GP_OUT 0b01
#define GP_IN 0b00
#define GP_ALT 0b10
#define GP_ANLG 0b11

