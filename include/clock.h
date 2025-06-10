#pragma once

#include "hardware.h"
#ifdef __HARDWARE_HEAD
#endif

#define ENABLE_POWER_CONTROLLER                                                \
  RCC->APB1ENR |= RCC_APB1ENR_PWREN_Msk;                                       \
  DUMMY_READ_FROM(RCC->APB1ENR);


void configure_clock(void);
void delay_ms(uint32_t ms);
void systick_handler(void);
