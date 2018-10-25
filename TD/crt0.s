.global _start
.syntax unified
.thumb_func

/*  This file is used to make the link edition of object files in order to create
    a executable. It set the stack pointer and calls a function to empty the bss. */
_start:
 LDR sp,=stack
 BL init_bss
 BL main
 BL _end
 
_end:
 BL _end
 