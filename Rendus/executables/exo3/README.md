# Exercice 3

---

## **Résultats de la taille des différentes sections.**
Commande utilisée : `objdump -h`


**File 1**
|         | taille O0 | taille O1 | taille O2 | taille Os |
| ------- | --------- | --------- | --------- | --------- |
| .text   | 000000b8  | 00000074  | 00000000  | 00000000  |
| .data   | 00000004  | 00000004  | 00000004  | 00000004  |
| .bss    | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata | 00000040  | 0000000e  | 0000000e  | 0000000e  |

**File 2**
|         | taille O0 | taille O1 | taille O2 | taille Os |
| ------- | --------- | --------- | --------- | --------- |
| .text   | 000000b8  | 00000074  | 00000000  | 00000000  |
| .data   | 00000004  | 00000004  | 00000004  | 00000004  |
| .bss    | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata |           |           |           |           |

**File 3**
|         | taille O0 | taille O1 | taille O2 | taille Os |
| ------- | --------- | --------- | --------- | --------- |
| .text   | 000000c0  | 00000070  | 00000000  | 00000000  |
| .data   | 00000008  | 00000008  | 00000008  | 00000008  |
| .bss    | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata |           | 00000030  |           |           |

**File 4**
|         | taille O0 | taille O1 | taille O2 | taille Os |
| ------- | --------- | --------- | --------- | --------- |
| .text   | 000000bc  | 00000074  | 00000000  | 00000000  |
| .data   | 00000004  | 00000004  | 00000004  | 00000004  |
| .bss    | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata | 00000034  | 00000004  | 00000004  | 00000004  |

## **Analyse global**

1. La section **.bss** est la même dans tous les cas. La variable statique non initialisée `z` de un octet est enregistre dans cette section, d'où sa taille.
2. La taille de la section **.data** (4 octets) vient de la variable globale initialisée `x` dont la taille est 32 bits. La taille varie uniquement dans le fichier 3 où le pointeur `mesg` vers la chaine de caractères est stocké, car il s'agit d'un pointeur global initialisé. On peut verifier ceci grâce à la commande `objdump -t`

## **Question 1**
La section .rodata du fichier `-O0` contient 64 octets qui correspondent aux 32 octets de la chaîne à utiliser pour le deuxième appel au printf, à la taille du tableau de caratères `mesg` et à une copie de la chaine codée dans mesg sans le caractère (`\n`). Ces deux derniers occupent 16 bits chacun même si les chaînes font 14 et 13 bits en longueur.

La section .text comporte l'ensemble des instructions assembleur (46) de 32bits chacune. Il est a noter que il y a quelques instructions qui a priori ne sont pas très utiles comme les suites `LSL` et `LSR` (logical shift right/left)

La section .rodata du fichier `-O1` contient 14 octets qui correspondent aux 14 octets de la taille de la chaîne de caratères pointée par mesg. Il y a la section .rodata.srt1.4 qui a été ajoutée. Cette section contient la chaîne de caractères pour le deuxième appel au printf et la copie citée précedemment. 

La section .text comporte l'ensemble des instructions assembleur (46) de 32bits chacune. Il est a noter que il y a quelques instructions qui a priori ne sont pas très utiles comme les suites `LSL` et `LSR` (logical shift right/left)

