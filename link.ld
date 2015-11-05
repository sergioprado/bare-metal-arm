OUTPUT_FORMAT ("elf32-littlearm")
SEARCH_DIR(.)

STACK_SIZE = DEFINED(__stack_size__) ? __stack_size__ : 0x0400;

MEMORY
{
  INTERRUPTS   (rx)  : ORIGIN = 0x00000000, LENGTH = 0x00000100
  FLASH_CONFIG (rx)  : ORIGIN = 0x00000400, LENGTH = 0x00000010
  TEXT         (rx)  : ORIGIN = 0x00000410, LENGTH = 0x0003FBF0
  RAM          (rwx) : ORIGIN = 0x1FFFE000, LENGTH = 0x00008000
}

/* Section Definitions */
SECTIONS
{
    .interrupts :
    {
        KEEP(*(.isr_vector .isr_vector.*))
    } > INTERRUPTS

    .flash_config :
    {
        . = ALIGN(4);
        LONG(0xFFFFFFFF);
        LONG(0xFFFFFFFF);
        LONG(0xFFFFFFFF);
        LONG(0xFFFFFFFE);
    } > FLASH_CONFIG

    .text :
    {
        *(.text .text.* .gnu.linkonce.t.*)
        *(.glue_7t) *(.glue_7)
        *(.rodata .rodata* .gnu.linkonce.r.*)
    } > TEXT

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > TEXT

    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > TEXT

    . = ALIGN(4);
    _etext = .;
    _sidata = .;

    .data : AT (_etext)
    {
        _sdata = .;
        *(.data .data.*)
        . = ALIGN(4);
        _edata = . ;
    } > RAM

    /* .bss section which is used for uninitialized data */
    .bss (NOLOAD) :
    {
        _sbss = . ;
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = . ;
    } > RAM

    /* stack section */
    .co_stack (NOLOAD):
    {
        . = ALIGN(8);
        . += STACK_SIZE;
        _start_of_stack = . ;
    } > RAM

    . = ALIGN(4);
    _end = . ;
}
