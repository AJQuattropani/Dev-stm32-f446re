#pragma once
#include "hardware.h"
#ifdef __HARDWARE_HEAD
#endif

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


#define ENABLE_GPIO_A RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN_Pos)
#define ENABLE_GPIO_B RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOBEN_Pos)

#define GP_REG_SET(reg, val, pos) reg |= (val << pos)
#define GP_REG_TGB(reg, pos) reg ^= (1 << pos)
