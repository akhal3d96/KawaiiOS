ENTRY(kernel_main)

SECTIONS
{
   . = 0x1000;

  START_ADDRESS = .;
  CODE_SECTION = .;

  .text :
  {
    *(.text)
  }

  . = ALIGN(4096);
  DATA_SECTION = .;

  .data :
  {
     *(.data)
     *(.rodata)
  }

   . = ALIGN(4096);
  BSS_SECTION = .;

  .bss :
  {
    *(.bss)
  }

  . = ALIGN(4096);
  END_ADDRESS = . ;
}