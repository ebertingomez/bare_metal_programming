MEMORY
	{
	  flash (rx) : ORIGIN = 0x00000000, LENGTH = 1M
	  sdram1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
	  sdram2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
	  
	}
stack = ORIGIN(sdram2) + LENGTH(sdram2) ;

SECTIONS {
	_astartROM = . ;
	.arm : {
		_astartRAM =  . ;
		*(.arm*)
		_aendRAM = . ; 
} > sdram1 AT > flash

	_tstartROM = . ;
	.text : {
		_tstartRAM =  . ;
		*(.text*)
		_tendRAM = . ;  
} > sdram1 AT > flash
	 
	.rodata : {
		*(.rodata*)
} > flash
		
	_dstartROM = . ;
	.data : {
		_dstartRAM =  . ;
	  	*(.data*)   
		_dendRAM = . ;   
} > sdram1 AT > flash

	.bss _dendRAM : {
		_bstart =  . ;
		*(.bss*)
		*(*COM*)
		_bend = . ;
} > sdram1
}

ENTRY(_start)