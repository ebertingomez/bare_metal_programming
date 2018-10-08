MEMORY
	{
	  flash (rx) : ORIGIN = 0x00000000, LENGTH = 1M
	  sdram1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
	  sdram2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
	}

SECTIONS {
	.text : {
		*(.text*)
} > sdram1
	 
	.rodata : {
		*(.rodata*)
} > sdram1
		
	.data : {
	  	*(.data*)      
} > sdram1
		
	.bss : {
		*(*bss*)
		*(*COM*)
} > sdram1

start_of_BSS  = ADDR(.bss);
size_of_BSS = SIZEOF(.bss);
stack = start_of_BSS + size_of_BSS;

}

ENTRY(_start)