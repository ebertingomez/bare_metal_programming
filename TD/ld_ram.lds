MEMORY
	{
	  flash (rx) : ORIGIN = 0x00000000, LENGTH = 1M
	  sdram1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
	  sdram2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
	  
	}

stack = ORIGIN(sdram2) + LENGTH(sdram2) ;

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
		_bstart =  . ;
		*(.bss*)
		*(*COM*)
		_bend = . ;
} > sdram1
}

ENTRY(_start)