# Exercice 3

---

## **Résultats de la taille des différentes sections.**
Commandes utilisées : `objdump -h`


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
| .text.*        | 000000c0  | 00000070  | 00000070  | 0000006c  |
| .data          | 00000008  | 00000008  | 00000008  | 00000008  |
| .bss           | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata        | 00000030  |           |           |           |
| .rel.text.*    | 00000040  | 00000038  | 00000038  | 00000038  |
| .rodata.str1.* |           | 0000002e  | 0000002e  | 0000002e  |
| .rel.data.*    | 00000008  | 00000008  | 00000008  | 00000008  |

**File 4**

|                | taille O0 | taille O1 | taille O2 | taille Os |
| -------------- | --------- | --------- | --------- | --------- |
| .text.*        | 000000bc  | 00000074  | 00000074  | 00000070  |
| .data          | 00000004  | 00000004  | 00000004  | 00000004  |
| .bss           | 00000001  | 00000001  | 00000001  | 00000001  |
| .rodata        | 00000034  | 00000004  | 00000004  | 00000004  |
| .rel.text.*    | 00000040  | 00000040  | 00000040  | 00000040  |
| .rodata.str1.* |           | 0000003e  | 0000003e  | 0000003b  |
| .rel.rodata.*  | 00000008  | 00000008  | 00000008  | 00000008  |

## **Analyse global**

1. La section **.bss** est la même dans tous les cas. La variable statique non initialisée `z` de un octet est enregistre dans cette section, d'où sa taille.
2. La taille de la section **.data** (4 octets) vient de la variable globale initialisée `x` dont la taille est 32 bits. La taille varie uniquement dans le fichier 3 où le pointeur `mesg` vers la chaine de caractères est stocké, car il s'agit d'un pointeur global initialisé. On peut verifier ceci grâce à la commande `objdump -t`

## **Question 1**
La section .rodata du fichier `-O0` contient 64 octets qui correspondent aux 32 octets de la chaîne à utiliser pour le deuxième appel au printf, à la taille du tableau de caratères `mesg` et à une copie de la chaine codée dans mesg sans le caractère (`\n`). Ces deux derniers occupent 16 bits chacun même si les chaînes font 14 et 13 bits en longueur.

La section .text comporte l'ensemble des instructions assembleur (46) de 32bits chacune. Il est a noter que il y a quelques instructions qui a priori ne sont pas très utiles comme les suites `LSL` et `LSR` (logical shift right/left). De plus, il y a la section `.rel.text` avec tout le code à être relocalisé lors de l'édition des liens. Ici on peut trouver des réferences  vers les variables `*COM* `, les fonctions externes (`print` et `puts`), et vers `.bss `et `.rodata` grâce à `readelf -r`.

La section `.rodata` du fichier `-O1` contient 14 octets qui correspondent aux 14 octets de la taille de la chaîne de caratères pointée par mesg. Il y a la section `.rodata.srt1.4` qui a été ajoutée. Cette section contient la chaîne de caractères pour le deuxième appel au printf et la copie citée précedemment. Cette section comporte la copie partielle de `mesg` avec un alignement de 4 octets et où chaque caratère comporte 1 octet. Cette section "temporelle" permet d'économiser de la place mémoire. En effet, elle sera utilisée pour la relocalisation du code au lieu de `.rodata`. Cette section comporte les chaînes qui seront affichées finalement.

La section .text comporte l'ensemble des instructions assembleur (28) de 32bits chacune. Les suites `LSL` et `LSR`  ont été supprimées. De plus, la reférence vers la section `.rel.text` est présente comme dans le fichier précedent, sauf que `.rodata.srt1.4` est enregistré au lieu de `.rodata`. De plus, on ne relocalise pas la variable `x`

Le fichier `-O2` contient presque les mêmes zones de données que le fichier objet `-O1`. La seule variation est la zone `.text` et `.rel.text` qui ont été renommés `.text.startup` et `.rel.text.startup`. Ceci est dû à la optimisation faite qui permet la réorganisation de fonctions. L'éditeur de liens positionnera cette section, qui comporte le `main`, au début de la zone `.data`. En effet, le `main` n'est souvent appélé qu'une seule fois et au début de l'éxecution. D'où le prefixe ajouté.

Le fichier `-Os` contient presque la même structure que le précedent, sauf que sa section read-only permet un aligment **d'un octet** qui permet d'économiser de la place mémoire. On peut trouver ainsi la section `.rodata.srt1.1` au lieu de `.rodata.srt1.4`

## **Question 2**
Tous les fichiers objets compilés à partir du fichier2 (`static const char mesg[]`) ont presque les mêmes sections que leur équivalent de la question précedente. La seule qui varie est `.rodata`. Pour toutes les optimisations (tous les fichiers sauf `-O0`), le compilateur n'enregistre pas la chaine de caractères `mesg` et garde sa copie partielle qui sera affichée par `puts`. En effet, cette chaîne ne peut être vue que dans le fichier oû elle est déclarée et elle n'est utilisée qu'une seule fois comme input de `puts`. Donc, le compilateur ne l'enregistre pas dans la section `.rodata` afin d'économiser de la place mémoire.

## **Question 3**
### Fichier 3
La principale différence entre les fichiers objet 2 et 3 est que ce dernier comporte un pointeur vers une chaîne de caractères au lieu d'un tableau de `char`. Ce pointeur est inclus dans la partie `.data` (cf. Analyse Global). Une réference vers la chaîne de caractères à laquelle il pointe est incluse dans `.rel.rodata`, car cette chaîne doit être relocalisée au moment de l'édition de liens et une adresse finale lui sera attribuée.


De plus, on n'utilise pas `puts`, car cette fonction requiert une chaîne(tableau) de caractères finie comme input pour après ajouter un saut de ligne à la fin. Le compilateur ne peut assurer que le pointeur de type global (qui a priori peut changer de référence à n'importe quel moment) pointe vers une chaîne "finie". Donc on utilise `printf` et on n'a pas besoin de recopier la chaîne dans `.rodata`. C'est pourquoi cette section fait 48 octets sans optimisations et 47 octets avec des optimisations (`.rodata.str1`). On perd un octet à cause de l'alignement. 

La section `.text` varie logiquement à cause de la modification du code (printf, dereférencements du pointeur) qui implique l'utilisation des differentes instructions assembleur.

### Fichier 4
La principale différence entre les fichiers objet 2 et 4 est que ce dernier comporte un pointeur constante vers une chaîne de caractères. Il est inclus toujours dans la section `.rodata` (cf. Analyse Global). Une réference vers la chaîne de caractères à laquelle il pointe est incluse dans `.rel.rodata`, car elle doit être relocalisée au moment de l'édition de liens et une adresse finale lui sera attribuée.

On utilise `puts` comme dans les questions précedentes, car on traite un pointeur constant qui, une fois initialisé à une valeur determiné, restera inchangé. Par contre, on recopie partiellement la chaîne en supprimant le saut de ligne de la fin. Puis on enregistre les deux chaînes dans `.rodata.str1` car on en a besoin pour `puts` et pour le pointeur qui, en tant que pointeur constant **global**, peut être appelé par d'autres fonctions et fait réference à cette chaîne.

La section `.rel.text` est presque la même que pour la question 2. La seule variation est pour le fichier `-O0` qui utilise 2 `printf` au lieu d'un `printf` et un `puts`. D'où la difference dans `.rodata ` pour dans ce cas. pour le fichier 4 compilé sans optimisation, on utilise `printf` qui est plus lourde. Par contre on n'a pas besoin de recopier la chaîne vu que l'on n'utilise pas `puts` à difference du fichier 2. D'où la taille de `.rodata` est plus petite.

La section `.text` varie logiquement à cause de la modification du code (printf, dereférencements du pointeur) qui implique l'utilisation des différentes instructions assembleur.