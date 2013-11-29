MEMORY
{
	CODE (rx) : ORIGIN = 0x00000000, LENGTH = 0x00080000
	DATA (rw) : ORIGIN = 0x00080000, LENGTH = 0x00080000
}

SECTIONS
{
	. = 0x0;
	.text :	{ *(.text) }
	. = 0x89000;
	.data : { *(.data) }
	.bss  : { *(.bss)  }
}
