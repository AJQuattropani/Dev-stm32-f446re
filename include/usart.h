#pragma once

#include "hardware.h"

#define ENABLE_USART2_CLOCK                                                    \
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN_Msk;                                    \
  DUMMY_READ_FROM(RCC->APB1ENR);

void usart_init(USART_TypeDef *usart);

void usart_write(USART_TypeDef *usart, char c);
