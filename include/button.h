#pragma once

#include "hardware.h"

#define ENABLE_IRQ_CLOCK                                                       \
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN_Msk;                                    \
  DUMMY_READ_FROM(RCC->APB2ENR);

void user_button_init();

