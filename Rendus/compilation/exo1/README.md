# Compilation Partie 1
***
## Exercice 1

Si la variable **i** est un int, il faut enlever l'instruction `AND rx, 0xFF` (voir exercice1bis.s), car le
processeur (en mode ARM) traite des donnés de **32bits** par défaut qui correspondent à la taille d'un int. 

Il est nécessaire de utiliser cette instruction pour le premier cas pour ne pas garder que les  huit premiers bits et traiter des **uint8_t**

## Exercice 2
Le compilateur charge deux fois le contenu de **\*c**, car il utilise le registre **IP** pour enregistrer **\*c** au début. 

 Le registre  **IP** est temporaire et peut varier au cours de l'exécution , car il est un *scratch register* . Donc il faut le charger de nouveau pour s'assurer que l'on utilise la bonne valeur pointée par **a**.