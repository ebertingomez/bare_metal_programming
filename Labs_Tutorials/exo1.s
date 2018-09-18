.syntax unified
.cpu cortex-m4
.thumb 

Start: 
 LDR r0,=0xdeadbeef
 LDR r1,=0x100
 LDR r2,=0x200

Loop:
 STR r0, [r1], #4
 CMP r1,r2
 BNE Loop

Copy:
 LDR r1,=0x300
 LDR r2,=0x400

Loop2:
 STR r0, [r1], #4
 CMP r1,r2
 BNE Loop2
End:
 B end