#include <stdint.h>

#define PERIPHERAL_BASE (0x40000000U) // location of RCC 
#define AHB1_BASE (PERIPHERAL_BASE + 0x20000U) // location of Advanced Hardware Bus 1
#define GPIOA_BASE (AHB1_BASE + 0x0U) // offset into AHB1 of GPIOA
#define RCC_BASE (AHB1_BASE + 0x3800U) // offset into AHB1 of RCC

#define RCC_AHB1ENR_OFFSET (0x30U) // offset into RCC for "RCC AHB1 peripheral clock enable register"
#define RCC_AHB1ENR ((volatile uint32_t*) (RCC_BASE + RCC_AHB1ENR_OFFSET)) // pointer to clock enable register
#define RCC_AHB1ENR_GPIOAEN (0x00U) // bit 0 of register enables GPIOA

/* 
* MODER configuration:
* 0b00: Input (reset state)
* 0b01: Generate Purpose OUTPUT mode
* 0b10: Alternate function mode
* 0b11: Analog mode
*/
#define GPIO_MODER_OFFSET (0x00U) // offset of mode register in GPIOA section of ADHB1
#define GPIOA_MODER ((volatile uint32_t*) (GPIOA_BASE + GPIO_MODER_OFFSET)) // pointer to gpio mode register
#define GPIO_MODE_MODER5 (10U) // two mode bits for each pin, so to access pin 5: offset of 10 
#define GPIO_ODR_OFFSET (0x14U) // offset of GPIO output data register from GPIOA section
#define GPIOA_ODR ((volatile uint32_t*) (GPIOA_BASE + GPIO_ODR_OFFSET)) // pointer to GPIOA out data register

#define LED_PIN 5 // pin 5 is at bit 5, just 1 bit for each output

#define GP_OUT 0b01
#define GP_IN 0b00
#define GP_ALT 0b10
#define GP_ANLG 0b11

void main(void)
{
  *RCC_AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN); // sets the bit to enable GPIOA
  
  // two dummy reads after enabling peripheral clock per errata
  volatile uint32_t dummy;
  dummy = *(RCC_AHB1ENR);
  dummy = *(RCC_AHB1ENR);

  *GPIOA_MODER |= (GP_OUT << GPIO_MODE_MODER5); // sets GPIOA to turn pin 5 to output

  while (1)
  {
    *GPIOA_ODR ^= (1 << LED_PIN); // flip bit 5 of the GPIOA out data register
    for (uint32_t i = 0; i < 1000000/2; i++); // busy wait
  }

}


