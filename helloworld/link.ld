/* Set the entry point on startup to the function reset_handler. */
ENTRY(reset_handler)

MEMORY {
  FLASH (rx): ORIGIN = 0x08000000, LENGTH = 2048K /* Flash memory: x0800 0000 - x0820 0000*/
  SRAM1 (rwx): ORIGIN = 0x20000000, LENGTH = 112K /* Ram 1: aliased: x2000 0000 - x2001 C000*/
  SRAM2 (rwx): ORIGIN = 0x2001CD00, LENGTH - 16K /* Ram 2: aliased: x2001 C000 - x2002 0000*/
}

/*
 * '.' is a location counter. It increments when adding enough space for text, rodata, etc. 
 * and it snaps upward to nearest 4 byte boundary via ALIGN. 
 */
SECTIONS
{
  .isr_vector :
  {
  KEEP(*(.isr_vector)) /* interrupt service routine at 0x0 */
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.rodata)

    . = ALIGN(4);
    _etext = .;
  } >FLASH /* offset into start of flash */

  .data :
  {
    . = ALIGN(4);
    _sdata = .; /* start data*/

    *(.data)

    . = ALIGN(4);
    _edata = .; /* end data*/
  } >SRAM1 AT> FLASH /* virtual memory address AT > load memory address, where section is loaded onto the target*/
  /* data in SRAM1 will be saved in flash and copied during load */

  .bss :
  {
    . = ALIGN(4);
    _sbss = .; /* start bss*/
    *(.bss)

    . = ALIGN(4);
    _ebss = .; /* end bss*/
  } >SRAM1
  

}
