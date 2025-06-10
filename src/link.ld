/* Set the entry point on startup to the function reset_handler. */
ENTRY(reset_handler);
PROVIDE(reset_handler_0x004 = reset_handler);
PROVIDE(systick_handler_0x03C = systick_handler);

/* LQFP64 */

MEMORY {
  FLASH (rx): ORIGIN = 0x08000000, LENGTH = 512K /* Flash memory space: x0800 0000 - x0820 0000*/
  SRAM1 (rwx): ORIGIN = 0x20000000, LENGTH = 112K /* Ram 1: aliased: x2000 0000 - x2001 C000*/
  SRAM2 (rwx): ORIGIN = 0x2001CD00, LENGTH = 16K /* Ram 2: aliased: x2001 C000 - x2002 0000*/
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
    *(.text.*)
    *(.rodata)
    *(.rodata.*)
    KEEP(*(.init))
    KEEP(*(.fini))
    *(.eh_frame)
    *(.ARM.exidx)

    . = ALIGN(4);
    _etext = .;
  } >FLASH /* offset into start of flash */

  _sidata = LOADADDR(.data);

  .data :
  {
    . = ALIGN(4);
    _sdata = .; /* start data*/

    *(.data)
    *(.data.*)
    KEEP(*(.init_array))
    KEEP(*(.fini_array))

    . = ALIGN(4);
    _edata = .; /* end data*/
  } >SRAM1 AT> FLASH /* virtual memory address AT > load memory address, where section is loaded onto the target*/
  /* data in SRAM1 will be saved in flash and copied during load */

  .bss :
  {
    . = ALIGN(4);
    _sbss = .; /* start bss*/
    __bss_start__ = _sbss;
    
    *(.bss)
    *(.bss.*)

    . = ALIGN(4);
    _ebss = .; /* end bss*/
    __bss_end__ = _ebss;
  } >SRAM1
  

}
