#pragma once

#include "hardware.h"
#ifdef __HARDWARE_HEAD
#endif

void configure_clock(void); 
void delay_ms(uint32_t ms);
void systick_handler(void);
