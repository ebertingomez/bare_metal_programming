.syntax unified
.cpu cortex-m4
.arm

f:
 LDR r0, =a
 LDR r2, #0
 
Loop:
 BL g
 ADD r2, r2, #1
 AND r2, r2, 0xFF
 CMP r2, [r0]
 BNE Loop
 



@ Si la variable "i" est un int, il faut enlever la ligne 12 (AND) (voir exercice1bis.s)