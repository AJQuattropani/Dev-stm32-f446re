#include "clock.h"

volatile uint32_t ticks;

void systick_handler(void) { ticks++; }

void delay_ms(uint32_t ms) {
  uint32_t start = ticks;
  uint32_t end = start + ms;

  if (end < start) // overflow
  {
    while (ticks > start); // wait for ticks to wrap
  }

  while (ticks < end);
}


void configure_clock(void) { 
  /*
    * MCO from ST-LINK: MCO output of ST-LINK MCU is used as an input clock. This frequency cannot be changed, 8MHz.
    * Connected to PH0-OSC_IN/PF0/PD0
    * The following configuration is needed:
    * SB55 OFF and SB54 ON
    * SB16 and SB50 ON
    * R35 and R37 removed
    */
  
  // enable power controller to set voltage scale to 1
  // Reference: PWR power control register (Reference Manual)
  ENABLE_POWER_CONTROLLER;

  PWR->CR |= (0b11 << PWR_CR_VOS_Pos);
  // Flash controller set for 3V3 supply and 100MHz (Table 6 of Reference Manual)
  FLASH->ACR |= FLASH_ACR_LATENCY_3WS;

  RCC->CR |= RCC_CR_HSEBYP_Msk | RCC_CR_HSEON_Msk; // enable clock (to use OSCIN) and turn on
  WAIT_FOR(RCC->CR, RCC_CR_HSERDY_Msk);
  
  // 8 MHz HSE clock / M = 4 = 2 MHz for PLL input
  // clear the PLLM, PLLN, PLLP bits
  RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM_Msk | RCC_PLLCFGR_PLLN_Msk | RCC_PLLCFGR_PLLP_Msk); 
  RCC->PLLCFGR |= ((4 << RCC_PLLCFGR_PLLM_Pos)    | // M = 4 = 8MHzi / 2MHzo 
                   (200 << RCC_PLLCFGR_PLLN_Pos)  | // N = 200 = 400Mhzo / 2MHzi
                   (1 << RCC_PLLCFGR_PLLP_Pos)    | // P = 4 = 400Mhzi / 100Mhzo (why 1?)
                   (1 << RCC_PLLCFGR_PLLSRC_Pos)); // use P (?)

  // Set APB1 prescalar to 2
  // max clock of APB is 50 Mhz ( half of AHB)
  RCC->CFGR |= (0b100 << RCC_CFGR_PPRE1_Pos); // bit 2 = 2?
  // enable PLL and wait
  RCC->CR |= RCC_CR_PLLON_Msk;
  WAIT_FOR(RCC->CR, RCC_CR_PLLRDY_Msk);
  
  // Select PLL output as system clock
  RCC->CFGR |= (RCC_CFGR_SW_PLL << RCC_CFGR_SW_Pos);
  WAIT_FOR(RCC->CFGR, RCC_CFGR_SWS_PLL);

}

