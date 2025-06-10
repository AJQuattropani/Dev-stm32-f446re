#include "startup.h"

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss, _sidata;
void __libc_init_array();

void reset_handler(void)
{
  uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *flash_data = (uint8_t*) &_sidata; // load addr
  uint8_t *sram_data = (uint8_t*) &_sdata; // virt addr

  for (uint32_t i = 0; i < data_size; i++)
  {
    sram_data[i] = flash_data[i];
  }
  
  // zero fill .bss section in sram
  uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  uint8_t *bss = (uint8_t*) &_sbss;
  
  for (uint32_t i = 0; i < bss_size; i++)
  {
    bss[i] = 0;
  }

  __libc_init_array();
  main();
}



