# 42-minishell

https://docs.google.com/spreadsheets/d/1fFFHGhm2F-ofMvUcIhZnBonpcASGL8954YFBUODmQy0/edit#gid=0

(entre parenthèses = ligne correspondante du gdoc)

General problems :
- empty prompt => segfault.
- erreurs syntaxe comme > < ou ||| (par exemple) exit le shell au lieu de redonner le prompt après avoir affiché le message d'erreur.
- export sans argument --> choisi de suivre le man et de considérer comme une erreur.
- eu un segfault très inattendu au niveau du parser en testant export, ça faisait un moment que je testais des trucs sans exit le programme, peut-être dû aux leaks ? pas réussi à le reproduire en tout cas mais j'ai gardé le screen dans un coin au cas où.


ECHO : 
- (90) echo $ ==> attendu: $, obtenu: (empty)
- (92) echo $?$ ==> attendu: 0$, obtenu: 0
- (99) echo login is [$USER] ==> 
    attendu: login is [lmurtin]
    obtenu: login is [
- (101) echo non existing variable [$TOTO] ==> 
    attendu: non existing variable []
    obtenu: non existing variable [
- (104) echo $9HOME ==> attendu: HOME, obtenu: (empty)
- (105) echo $HOME% ==> attendu: /mnt/nfs/homes/lmurtin%
                        obtenu: (empty)
- (131) echo "$""" ==> attendu: $, obtenu: (empty)
- (133/135) echo $"HOME" et echo $""HOME et echo $''HOME ==> 
    attendu: HOME, obtenu: (empty)
- (143) echo ''$HOME ==> attendu: /mnt/nfs/homes/lmurtin
                    obtenu: $HOME
- (145 à 151) echo $ suivi de diverse combinaisons de lettres et quotes => obtenu: (empty) pour diverses attendus

EXPORT :
- (218) export "" ==> attendu: "Not a valid identifier"
                        obtenu: "Too few arguments" (la commande export ne recoit pas la chaine vide en tant qu'argument)


# Tutoriel Magic Malloc

* MALLOC : Si tu souhaites effectuer un malloc, cela tient en une ligne (il faut juste indiquer la size) :

node = magic_malloc(MALLOC, sizeof(t_token), NULL);

* ADD : Si tu utilises une fonction de la libft qui malloc qqch (ft_strdup, ft_strjoin), apres avoir utilise la fonction, il faut rajouter une ligne (dans laquelle il faut juste indique l'element en question qui a ete malloc) :

result = ft_substr(str, 0, i);

magic_malloc(ADD, 0, result);

* FREE : Si tu souhaites free un seul element, il faut utiliser cette ligne (par exemple pour free tmp) (en indiquant seulement l'element a free) :

magic_malloc(FREE, 0, tmp);

* QUIT : Si tu souhaites free tout ce que tu as malloc depuis le debut de ton programme et quitter, c'est cette ligne :

magic_malloc(QUIT, 0, NULL);

