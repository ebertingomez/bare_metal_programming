.syntax unified
.cpu cortex-m4
.arm

Begin:
 LDR r0, =a
 LDR r1, [r0]
 LDR r2, [r1]
 LDR r3, =b
 LDR r4, [r3]
 LDR r5, [r4]
 LDR r6, =c
 LDR r7, [r6]
 LDR r8, [r7]
 ADD r2, r2, r8
 ADD r5, r5, r8