Apres avoir decompile le programme et reformate le code, on se rend compte que le programme prend en entree du stdin un nombre qui va etre utilise comme cle de decryptage.
Il faut entrer le bon nombre pour que le programme execute /bin/sh. On se rend compte que le programme ne prend en compte l'entree que pour certains nombres, donc on teste ceux-ci.

Voici tous les cas qui sont pris en compte:

diff == 1
diff == 2
diff == 3
diff == 4
diff == 5
diff == 6
diff == 7
diff == 8
diff == 9
diff == 16
diff == 17
diff == 18
diff == 19
diff == 20
diff == 21

On retrouve la valeur de a mise en entree pour chaque cas:

diff = b - a
diff + a = b
a = b - diff

322424845 - 1 = 322424844
322424845 - 2 = 322424843
322424845 - 3 = 322424842
322424845 - 4 = 322424841
322424845 - 5 = 322424840
322424845 - 6 = 322424839
322424845 - 7 = 322424838
322424845 - 8 = 322424837
322424845 - 9 = 322424836
322424845 - 16 = 322424829
322424845 - 17 = 322424828
322424845 - 18 = 322424827
322424845 - 19 = 322424826
322424845 - 20 = 322424825
322424845 - 21 = 322424824

En testant on trouve que la valeur 322424827 fonctionne.

