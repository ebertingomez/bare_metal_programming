.global _start
.syntax unified

_start:
 LDR sp,=0x20000000
 B main
