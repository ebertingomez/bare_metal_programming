.global _start
.syntax unified

_start:
 LDR sp,=stack
 BL init_bss
 BL main
 BL _end
 
_end:
 BL _end
 