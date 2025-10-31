Apres avoir decompile le programme et reformate le code, on se rend compte que le programme prend en entree du stdin un nombre qui va etre utilise comme cle de decryptage.
Il faut entrer le bon nombre pour que le programme execute /bin/sh. On se rend compte que le programme ne prend en compte l'entree que pour certains nombres, donc on teste ceux-ci.
Le nombre 8 fonctionne.