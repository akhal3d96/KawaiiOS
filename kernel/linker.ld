ENTRY(start)
SECTIONS
{
    . = 1M;
  .text BLOCK(4K): ALIGN(4K)
  {
      code = .;
      *(.mboot)
      *(.text)
  }

   .rodata BLOCK(4K): ALIGN(4K)
  {
      rodata = .;
      *(.rodata)
  }

  .data BLOCK(4K): ALIGN(4K)
  {
      data = .;
      *(.data)
      *(.rodata)
  }

  .bss BLOCK(4K): ALIGN(4K)
  {
      bss = .;
      *(COMMON)
      *(.bss)
  }

  end = .;
}