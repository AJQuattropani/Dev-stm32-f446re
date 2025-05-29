/* Set the entry point on startup to the function reset_handler. */
ENTRY(reset_handler)

MEMORY {
  FLASH (rx): ORIGIN = 0x08000000, LENGTH = 512K
  SRAM1 (rwx): ORIGIN = 0x20000000, LENGTH = 112K
  SRAM2 (rwx): ORIGIN = 0x2001CD00, LENGTH - 16K
}

/*
 * '.' is a location counter. It increments when adding enough space for text, rodata, etc. 
 * and it snaps upward to nearest 4 byte boundary via ALIGN. 
 */
SECTIONS
{
  .isr_vector :
  {
  KEEP(*(.isr_vector))
  } >FLASH

  .text :
  {
    /* I guess _stext is automatically defined.*/
    . = ALIGN(4);
    *(.text)
    *(.rodata)

    . = ALIGN(4);
    _etext = .;
  } >FLASH

  .data :
  {
    . = ALIGN(4);
    _sdata = .; /* start data*/

    *(.data)

    . = ALIGN(4);
    _edata = .; /* end data*/
  } >SRAM AT> FLASH /* virtual memory address AT > load memory address, where section is loaded onto the target*/

  .bss :
  {
    . = ALIGN(4);
    _sbss = .; /* start bss*/
    *(.bss)

    . = ALIGN(4);
    _ebss = .; /* end bss*/
  } >SRAM


}
