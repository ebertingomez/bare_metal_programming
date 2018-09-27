.syntax unified
.cpu cortex-m4
.arm

f:
 LDR r0, =a
 LDR r2, #0
 
Loop:
 BL g
 ADD r2, r2, #1
 @ La instruction suivante a été ajoutée après avoir vu la le fichier .c compilé.
 @ Cette instruction fait en sorte de traiter la variable "a" comme un uint8_t
 AND r2, r2, 0xFF
 CMP r2, [r0]
 BNE Loop
 



@ Si la variable "i" est un int, il faut enlever la ligne 14 (AND) (voir exercice1bis.s)