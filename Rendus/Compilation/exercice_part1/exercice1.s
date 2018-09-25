.syntax unified
.cpu cortex-m4
.arm

Start:
 LDR r0, =a
 LDR r1, =i
 LDR r2, #0
 STR r2, [r1]
 
Loop:
 BL g
 ADD r2, r2, #1
 STR r2, [r1]
 CMP r2, [r0]
 BNE Loop
 
End:
 B end


% Si la variable "i" est un int, le code est le meme.