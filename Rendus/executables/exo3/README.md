# Exercice 3

---

## **Résultats de la taille des différentes sections.**
Commande utilisée : `objdump -h`


**File 1**
|                | taille O0 | taille O1 | taille O2 | taille Os |
| -------------- | --------- | --------- | --------- | --------- |
| .text.*        | 000000b8  | 00000074  | 00000074  | 00000070  |
| .data          | 00000004  | 00000004  | 00000004  | 00000004  |
| .bss           | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata        | 00000040  | 0000000e  | 0000000e  | 0000000e  |
| .rel.text.*    | 00000040  | 00000040  | 00000040  | 00000040  |
| .rodata.str1.* |           | 00000030  | 00000030  | 0000002d  |

**File 2**
|                | taille O0 | taille O1 | taille O2 | taille Os |
| -------------- | --------- | --------- | --------- | --------- |
| .text.*        | 000000b8  | 00000074  | 00000074  | 00000070  |
| .data          | 00000004  | 00000004  | 00000004  | 00000004  |
| .bss           | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata        | 00000040  |           |           |           |
| .rel.text.*    | 00000040  | 00000040  | 00000040  | 00000040  |
| .rodata.str1.* |           | 00000030  | 00000030  | 0000002d  |

**File 3**
|                | taille O0 | taille O1 | taille O2 | taille Os |
| -------------- | --------- | --------- | --------- | --------- |
| .text.*        | 000000c0  | 00000070  | 00000000  | 00000000  |
| .data          | 00000008  | 00000008  | 00000008  | 00000008  |
| .bss           | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata        |           | 00000030  |           |           |
| .rel.text.*    |           |           |           |           |
| .rodata.str1.* |           |           |           |           |

**File 4**
|                | taille O0 | taille O1 | taille O2 | taille Os |
| -------------- | --------- | --------- | --------- | --------- |
| .text.*        | 000000bc  | 00000074  | 00000000  | 00000000  |
| .data          | 00000004  | 00000004  | 00000004  | 00000004  |
| .bss           | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata        | 00000034  | 00000004  | 00000004  | 00000004  |
| .rel.text.*    |           |           |           |           |
| .rodata.str1.* |           |           |           |           |

## **Analyse global**

1. La section **.bss** est la même dans tous les cas. La variable statique non initialisée `z` de un octet est enregistre dans cette section, d'où sa taille.
2. La taille de la section **.data** (4 octets) vient de la variable globale initialisée `x` dont la taille est 32 bits. La taille varie uniquement dans le fichier 3 où le pointeur `mesg` vers la chaine de caractères est stocké, car il s'agit d'un pointeur global initialisé. On peut verifier ceci grâce à la commande `objdump -t`

## **Question 1**
La section .rodata du fichier `-O0` contient 64 octets qui correspondent aux 32 octets de la chaîne à utiliser pour le deuxième appel au printf, à la taille du tableau de caratères `mesg` et à une copie de la chaine codée dans mesg sans le caractère (`\n`). Ces deux derniers occupent 16 bits chacun même si les chaînes font 14 et 13 bits en longueur.

La section .text comporte l'ensemble des instructions assembleur (46) de 32bits chacune. Il est a noter que il y a quelques instructions qui a priori ne sont pas très utiles comme les suites `LSL` et `LSR` (logical shift right/left). De plus, il y a la section `.rel.text` avec tout le code à être relocalisé lors de l'édition des liens. Ici on peut trouver des réferences  vers les variables `*COM* `, les fonctions externes (`print` et `puts`) et vers le `.bss `et `.rodata`. 

La section `.rodata` du fichier `-O1` contient 14 octets qui correspondent aux 14 octets de la taille de la chaîne de caratères pointée par mesg. Il y a la section `.rodata.srt1.4` qui a été ajoutée. Cette section contient la chaîne de caractères pour le deuxième appel au printf et la copie citée précedemment. Cette section comporte la copie partielle de `mesg` avec un alignement de 4 octets et où chaque caratère comporte 1 octet. Cette section "temporelle" permet d'économiser de la place mémoire. En effet, elle sera utilisée pour la relocalisation du code au lieu de `.rodata`. Cette section comporte les chaînes qui seront affichées finalement.

La section .text comporte l'ensemble des instructions assembleur (28) de 32bits chacune. Les suites `LSL` et `LSR`  ont été supprimées. De plus, la reférence vers la section `.rel.text` est présente comme dans le fichier précedent, sauf que `.rodata.srt1.4` est enregistré au lieu de `.rodata`. De plus, on ne relocalise pas la variable `x`

Le fichier `-O2` contient presque les mêmes zones de données que le fichier objet `-O1`. La seule variation est la zone `.text` et `.rel.text` qui ont été renommés `.text.startup` et `.rel.text.startup`. Ceci est dû à la optimisation faite qui permet la réorganisation de fonctions. L'éditeur de liens positionnera cette section, qui comporte le `main`, au début de la zone `.data`. En effet, le `main` n'est souvent appélé qu'une seule fois et au début de l'éxecution. D'où le prefixe ajouté.

Le fichier `-Os` contient presque la même structure que le précedent, sauf que sa section read-only permet un aligment **d'un octet** qui permet d'économiser de la place mémoire. On peut trouver ainsi la section `.rodata.srt1.1` au lieu de `.rodata.srt1.4`

## **Question 1**
