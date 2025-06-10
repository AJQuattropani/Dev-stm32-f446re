#pragma once

#include <stdint.h>
#include <stdio.h>
#include "usart.h"
#include "clock.h"

volatile uint32_t ticks;
void configure_clock(void);
void systick_handler_0x03C(void) { ticks++; }
void delay_ms(uint32_t ms);


void main(void);
