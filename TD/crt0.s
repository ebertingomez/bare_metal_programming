.global _start
.syntax unified

_start:
 LDR sp,=0x10001000
 BL init_bss
 BL main
 BL _end
 
_end:
 BL _end
 