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
 STR r2, [r1]
 ADD r5, r5, r8
 STR r5, [r4]

 // Le compilateur charge deux fois le contenue de *c, car il utilise le registre "ip" pour enregistrer *c au debut. 
 // Ce registre est temporaire et peut varier au cours de l'execution. Donc il faut le charger de nouveau pour s'assurer
 // que l'on utilise la bonne valeur