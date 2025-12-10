# 1 ère solution


Le programme level06 prend en entree une chaine et un nombre. Il s'assure que la chaine rentre dans certaines contraintes, hash la chaine et s'assure que le nombre correspond au hash.

La chaine doit etre plus grande que 4 caracteres, et ne doit contenir que des caracteres affichables.

Il suffit de re-ecrire le code en ajoutant un print du hash pour trouver un combinaison qui fonctionne.

La combinaison suivante fonctionne:
abcdefgh
6234502

# 2ème solution

## le programme
Le programme level06 prend en entree une chaine et un nombre. Il s'assure que la chaine rentre dans certaines contraintes, hash la chaine et s'assure que le nombre correspond au hash.

La chaine doit etre plus grande que 4 caracteres, et ne doit contenir que des caracteres affichables.


## La faille
L'idée est de bypass la condition qui vérifie la valeur de retour du  `ptrace` en remplaçant cette valeur par 0.

Il faut aussi trouver l'adresse ou est stocké la variable hash.

Pour ce faire on va avoir besoin de faire deux breakpoint, le premier sera juste après le call ptrace et le second juste avant la comparaison finale.

```
(gdb) disas auth
Dump of assembler code for function auth:
   0x08048748 <+0>:	push   %ebp
   0x08048749 <+1>:	mov    %esp,%ebp
   0x0804874b <+3>:	sub    $0x28,%esp
   ...
   0x080487b5 <+109>:	call   0x80485f0 <ptrace@plt>
   0x080487ba <+114>:	cmp    $0xffffffff,%eax
   0x080487bd <+117>:	jne    0x80487ed <auth+165>
   0x080487bf <+119>:	movl   $0x8048a68,(%esp)
   0x080487c6 <+126>:	call   0x8048590 <puts@plt>
    ...
   0x08048866 <+286>:	cmp    -0x10(%ebp),%eax
   0x08048869 <+289>:	je     0x8048872 <auth+298>
   0x0804886b <+291>:	mov    $0x1,%eax
   0x08048870 <+296>:	jmp    0x8048877 <auth+303>
   0x08048872 <+298>:	mov    $0x0,%eax
   0x08048877 <+303>:	leave  
   0x08048878 <+304>:	ret    
End of assembler dump.
```

break *0x080487ba
break *0x08048869

L'étape suivante est de modifier l'eax juste après le breakpoint pour bypass la condition.

```
Breakpoint 1, 0x080487ba in auth ()
(gdb) info registers eax
eax            0xffffffff	-1
(gdb) set $eax = 0
(gdb) info registers eax
eax            0x0	0
```

Il faut désormais récupérer la valeur du hash qui est stocké à l'adresse de la variable à l'adresse `0x10(%ebp)`

```
Breakpoint 2, 0x08048869 in auth ()
(gdb) x/wx $ebp-0x10
0xffffd5c8:	0x005f1ae2
(gdb) p 0x005f1ae2
$1 = 6232802
```

`x/wx` permet d'afficher les 4 octets de l'adresse en hexadécimal.

Il ne reste plus qu'à relancer le programme hors de GDB avec les même arguments.

```
level06@OverRide:~$ ./level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: abcdef
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6232802
Authenticated!
$ whoami
level07
```