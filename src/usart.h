#pragma once

#include "stm32f4xx.h"
#include <stdint.h>

void usart_init(USART_TypeDef *usart);

void usart_write(USART_TypeDef *usart, char c);
