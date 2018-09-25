.syntax unified
.cpu cortex-m4
.arm

f:
 LDR r0, =a
 LDR r2, #0
 
Loop:
 BL g
 ADD r2, r2, #1
 CMP r2, [r0]
 BNE Loop
 



