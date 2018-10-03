# Exercice 2

Afin de connaître l'ordre des sections d'un executable, j'ai créé un fichier .c avec des variables de différents natures et scope qui sont stockés dans des sections particulières. Pour être plus précis:

| Variable     | Section | Adresse          |
| ------------ | ------- | ---------------- |
| void funct() | .text   | 0000000000000804 |
| const int a  | .rodata | 00000000000008a4 |
| int c        | .data   | 0000000000201038 |
| int d        | .bss    | 0000000000201040 |

Les adresses ont été recupérées grâces à la commande `objdump -t`. Sinon on peut recupérer les adresses de départ des sections de l'éxécutable via `objdump -h` et en déduire l'ordre de stockage.

| Section | @VMA = @LMA      |
| ------- | ---------------- |
| .text   | 00000000000005d0 |
| .rodata | 00000000000008a0 |
| .data   | 0000000000201028 |
| .bss    | 000000000020103c |

Le fichier executable permet de retrouver les adresses des variables (a,c,d,e,f), de la fonction funct() et de l'adresse à laquelle le pointeur g fait reférence. Voici les résultats:

| Variable | Section     | Adresse        |
| -------- | ----------- | -------------- |
| funct()  | .text       | 0x55f034c7b804 |
| a        | .rodata     | 0x55f034c7b8c4 |
| c        | .data       | 0x55f034e7c038 |
| d        | .bss        | 0x55f034e7c040 |
| e        | pile(stack) | 0x7ffd2298b25c |
| f        | pile(stack) | 0x7ffd2298b258 |
| *g       | tas(heap)   | 0x55f0364c9010 |

On peut donc en conclure l'ordre des différentes sections mappées sur un PC Linux x86_64: 

**Ordre**
1. .text
2. .rodata
3. .data
4. .bss
5. tas
6. pile

Puis, on peut remarquer que la pile croît de façon descendante. En effet, les variables "e" et "f" ont été stockées dans la pile l'une après l'autre dans cet ordre. Comme l'adresse de e (**0x7ffd2298b25c**) et plus grande que celle de f (**0x7ffd2298b258**), on en déduit que la pile est en mode descending.

**Note:** On peut assurer que les variables "e" et "f" ont été initialisées dans cet ordre car on n'a  effectué aucune optimisation lors de la compilation (`CFLAGS -O0`)


