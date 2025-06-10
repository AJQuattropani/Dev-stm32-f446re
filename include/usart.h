#pragma once

#include "hardware.h"
#ifdef __HARDWARE_HEAD
#endif

void usart_init(USART_TypeDef *usart);

void usart_write(USART_TypeDef *usart, char c);
