# Exercice 3

---

## **Résultats de la taille des différentes sections.**
Commande utilisée : `objdump -h`


**File 1**
|         | taille Os | taille O0 | taille O1 | taille O2 |
| ------- | --------- | --------- | --------- | --------- |
| .text   | 00000000  | 000000b8  | 00000074  | 00000000  |
| .data   | 00000004  | 00000004  | 00000004  | 00000004  |
| .bss    | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata | 0000000e  | 00000040  | 0000000e  | 0000000e  |

**File 2**
|         | taille Os | taille O0 | taille O1 | taille O2 |
| ------- | --------- | --------- | --------- | --------- |
| .text   | 00000000  | 000000b8  | 00000074  | 00000000  |
| .data   | 00000004  | 00000004  | 00000004  | 00000004  |
| .bss    | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata |           |           |           |           |

**File 3**
|         | taille Os | taille O0 | taille O1 | taille O2 |
| ------- | --------- | --------- | --------- | --------- |
| .text   | 00000000  | 000000c0  | 00000070  | 00000000  |
| .data   | 00000008  | 00000008  | 00000008  | 00000008  |
| .bss    | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata |           | 00000030  |           |           |

**File 4**
|         | taille Os | taille O0 | taille O1 | taille O2 |
| ------- | --------- | --------- | --------- | --------- |
| .text   | 00000000  | 000000bc  | 00000074  | 00000000  |
| .data   | 00000004  | 00000004  | 00000004  | 00000004  |
| .bss    | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata | 00000004  | 00000034  | 00000004  | 00000004  |

## **Analyse**

1. La section .bss est la même dans tous les cas. La variable statique non initialisée `z` de un octet est enregistre dans cette section, d'où sa taille.
2. La taille de la section .data (4 octets) vient de la variable globale initialisée `x` dont la taille est 32 bits. La taille varie uniquement dans le fichier 3 où le pointeur `mesg` vers la chaine de charactères est stocké. On peut verifier ceci grâce à la commande `objdump -t`
3. 
