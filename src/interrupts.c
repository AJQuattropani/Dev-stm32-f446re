#include "interrupts.h"

extern volatile uint32_t ticks;
void systick_handler_0x03C(void) { ticks++; }

void default_handler(void) 
{
  while (1);
}

