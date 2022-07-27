# 42-minishell

General problems :
- empty prompt => segfault
- erreurs syntaxe comme > < ou ||| (par exemple) exit le shell au lieu de redonner le prompt après avoir affiché le message d'erreur


ECHO : (ligne correspondante du gdoc)
- echo $ ==> attendu: $, obtenu: (empty)
- echo "$""" ==> attendu: $, obtenu: (empty)
- (133/135) echo $"HOME" et echo $""HOME et echo $''HOME ==> 
    attendu: HOME, obtenu: (empty)
- echo $?$ ==> attendu: 0$, obtenu: 0
- echo login is [$USER] ==> 
    attendu: login is [lmurtin]
    obtenu: login is [
- echo non existing variable [$TOTO] ==> 
    attendu: non existing variable []
    obtenu: non existing variable [
- echo $9HOME ==> attendu: HOME, obtenu: (empty)
- (143) echo ''$HOME ==> attendu: /mnt/nfs/homes/lmurtin
                    obtenu: $HOME

