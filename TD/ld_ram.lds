MEMORY
	{
	  flash (rx) : ORIGIN = 0x00000000, LENGTH = 1M
	  sdram1 (!rx) : ORIGIN = 0x20000000, LENGTH = 96K
	  sdram2 (!rx) : ORIGIN = 0x10000000, LENGTH = 32K
	}

SECTIONS {
	.text : {
		*(.text)
} > sdram1
	 
	.rodata : {
		*(.rodata)
} > sdram1
		
	.data : {
	  	*(.data)      
} > sdram1
		
	.bss : {
		*(.bss) *(COMMON)
} > sdram1
}

ENTRY(main)