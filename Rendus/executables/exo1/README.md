# Exercice 1

Dans le slide 96 il n'y a rien à corriger. La valeur 4 affichée dans le champs des valeurs des objets correspond à la taille de la variable y (32 bits = 4 Octets). Ceci est verifié lorsqu'on la change.

 **32bitsBeforeLink**
```
00000004 g       *COM*		 00000004 y
```
 **64bitsBeforeLink**
```
00000008 g       *COM*		 00000008 y
```
**8bitsBeforeLink**
```
00000001 g       *COM*		 00000001 y
```

Puis, comme elle n'est pas définie au moment de sa déclaration, le compilateur l'enregistre dans la section temporaire \*COM\*, car il ne sait pas s'il faudrait stocker cette variable en dans .data ou .bss. Bien que cette variable soit définie dans le main, elle peut être définie dans un autre fichier comme variable globale. Elle se comporte donc comme une variable globale non instanciée (de même la variable w du fichier 32bits.c).

**32bitsBeforeLink**
```
00000004 g       *COM*		 00000004 y
00000004 g       *COM*		 00000004 w
```

Dans tous les cas précedents, la variable "y" est mise dans la section .bss après l'édition de liens, car elle est une variable globale et n'est pas définie. Donc, elle est instanciée à zero.

 **32bitsAfterLink**
```
00023258 g       .bss		 00000004 y
```

Si y est instanciée à zero avant l'édition des liens, le compilateur lui la stocke dans le .bss. Pour une autre valeur d'instantiation, elle est stockée dans .data, car c'est une variable globale. 

**zeroBeforeLink**
```
00000000 g       .bss		 00000004 y
```
**differentZeroBeforeLink**
```
00000000 g       .data		 00000004 y
```

Après l'édition de liens, ces objets restent dans mêmes sections qu'après la compilation (.bss et .data) sauf que leur adresse est calculée.
**zeroAfterLink**
```
0002320c g       .bss		 00000004 y
```
**differentZeroAfterLink**
```
0002283c g       .data		 00000004 y
```