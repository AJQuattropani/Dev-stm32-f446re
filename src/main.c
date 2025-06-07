#include <stdint.h>
#include "stm32f4xx.h"

/* #define PERIPHERAL_BASE (0x40000000U) // location of RCC 
#define AHB1_BASE (PERIPHERAL_BASE + 0x20000U) // location of Advanced Hardware Bus 1
#define GPIOA_BASE (AHB1_BASE + 0x0U) // offset into AHB1 of GPIOA
#define RCC_BASE (AHB1_BASE + 0x3800U) // offset into AHB1 of RCC

#define RCC_AHB1ENR_OFFSET (0x30U) // offset into RCC for "RCC AHB1 peripheral clock enable register"
#define RCC_AHB1ENR ((volatile uint32_t*) (RCC_BASE + RCC_AHB1ENR_OFFSET)) // pointer to clock enable register
#define RCC_AHB1ENR_GPIOAEN (0x00U) // bit 0 of register enables GPIOA
*/

/* 
* MODER configuration:
* 0b00: Input (reset state)
* 0b01: Generate Purpose OUTPUT mode
* 0b10: Alternate function mode
* 0b11: Analog mode
*/

/*
#define GPIO_MODER_OFFSET (0x00U) // offset of mode register in GPIOA section of ADHB1
#define GPIOA_MODER ((volatile uint32_t*) (GPIOA_BASE + GPIO_MODER_OFFSET)) // pointer to gpio mode register
#define GPIO_MODE_MODER5 (10U) // two mode bits for each pin, so to access pin 5: offset of 10 
#define GPIO_ODR_OFFSET (0x14U) // offset of GPIO output data register from GPIOA section
#define GPIOA_ODR ((volatile uint32_t*) (GPIOA_BASE + GPIO_ODR_OFFSET)) // pointer to GPIOA out data register
*/

#define LED_PIN 5 // pin 5 is at bit 5, just 1 bit for each output

/*
#define GP_OUT 0b01
#define GP_IN 0b00
#define GP_ALT 0b10
#define GP_ANLG 0b11
*/
uint32_t ticks;
void configure_clock(void);
void systick_handler_0x03C(void) { ticks++; }
void delay_ms(uint32_t ms);

void main(void)
{
  //configure_clock();
  //SystemCoreClockUpdate();
  //SysTick_Config(100000); // 10,000,000 / 100,000 = 1
  //__enable_irq();

  RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN_Pos); // sets the bit to enable GPIOA

  // two dummy reads after enabling peripheral clock per errata
  volatile uint32_t dummy;
  dummy = RCC->AHB1ENR;
  dummy = RCC->AHB1ENR;

  // GPIOA->MODER |= (GP_OUT << GPIO_MODE_MODER5); // sets GPIOA to turn pin 5 to output
  GPIOA->MODER |= (1 << GPIO_MODER_MODER5_Pos);

  while (1)
  {
    GPIOA->ODR ^= (1 << LED_PIN); // flip bit 5 of the GPIOA out data register
    for (uint32_t i = 0; i < 1000000/2; i++); // busy wait
    //delay_ms(500);
  }

}

void configure_clock(void) { 
  RCC->CR |= RCC_CR_HSEBYP_Msk | RCC_CR_HSEON_Msk; // enable clock and turn on
  while (!(RCC->CR & RCC_CR_HSERDY_Msk)); // wait for clock to become ready
  
  // enable power controller to set voltage scale to 1
  // Reference: PWR power control register (Reference Manual)
  RCC->APB1ENR |= RCC_APB1ENR_PWREN_Msk;
  volatile uint32_t dummy;
  dummy = RCC->APB1ENR;
  dummy = RCC->APB1ENR;
  PWR->CR |= (0b11 << PWR_CR_VOS_Pos);

  // Flash controller set for 3V3 supply and 100MHz (Table 6 of Reference Manual)
  FLASH->ACR |= FLASH_ACR_LATENCY_3WS;

  // 8 MHz HSE clock / M = 4 = 2 MHz for PLL input
  // clear the PLLM, PLLN, PLLP bits
  RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM_Msk | RCC_PLLCFGR_PLLN_Msk | RCC_PLLCFGR_PLLP_Msk);
  
  RCC->PLLCFGR &= ((4 << RCC_PLLCFGR_PLLM_Pos)    | // M = 4 = 8MHzi / 2MHzo 
                   (200 << RCC_PLLCFGR_PLLN_Pos)  | // N = 200 = 400Mhzo / 2MHzi
                   (1 << RCC_PLLCFGR_PLLP_Pos)    | // P = 4 = 400Mhzi / 100Mhzo (why 1?)
                   (1 << RCC_PLLCFGR_PLLSRC_Pos)); // use P (?)

  // Set APB1 prescalar to 2
  // max clock of APB is 50 Mhz ( half of AHB)
  RCC->CFGR |= (0b100 << RCC_CFGR_PPRE1_Pos); // bit 2 = 2?
  // enable PLL and wait
  RCC->CR |= RCC_CR_PLLON_Msk;
  while(!(RCC->CR & RCC_CR_PLLRDY_Msk));
  
  // Select PLL output as system clock
  RCC->CFGR |= (RCC_CFGR_SW_PLL << RCC_CFGR_SW_Pos);
  while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));
}

void delay_ms(uint32_t ms) {
  uint32_t start = ticks;
  uint32_t end = start + ms;

  if (end < start) // overflow
  {
    while (ticks > start); // wait for ticks to wrap
  }

  while (ticks < end);
}

