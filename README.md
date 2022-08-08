# (Derniers) cas qui ne fonctionnent pas

* quand on écrit exit dans le prompt, le programme quitte mais il reste 5 fd ouverts au lieu de 3

* echo -n "blabla" >> file

* OK : $_

* OK : "$USER"$USER'$USER'

* cat << ok << salut (il faut ecrire ok puis salut, or dans le bash il faut juste ecrire salut pour arreter la lecture)

* si je change la valeur de g_exit_status, cela n'a pas d'impact dans l'env quand je fais echo $?

# Cas pour lesquels il faut faire attention

* cat | cat | ls 

* ctrl c avec un cat

* export a+= (avec les concatenations)

* absolute / relative path

* cd with env -i

# Comment ignorer leaks de readline :

1. Compiler normalement.
2. Au lieu d'appeler `valgrind ./minishell`, il faut exécuter leakscheck.sh.
3. Enjoy :D

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
# 42-minishell

https://docs.google.com/spreadsheets/d/1fFFHGhm2F-ofMvUcIhZnBonpcASGL8954YFBUODmQy0/edit#gid=0

(entre parenthèses = ligne correspondante du gdoc)

General problems :
- OK : empty prompt => segfault.
- OK : " " " ==> "Wrong number of quotes" puis segfault.
- OK : erreurs syntaxe comme > < ou ||| (par exemple) exit le shell au lieu de redonner le prompt après avoir affiché le message d'erreur.
- export sans argument --> choisi de suivre le man et de considérer comme une erreur.
- [je pense que c'était en effet dû à l'absence totale de gestion des leaks haha] : eu un segfault très inattendu au niveau du parser en testant export, ça faisait un moment que je testais des trucs sans exit le programme, peut-être dû aux leaks ? pas réussi à le reproduire en tout cas mais j'ai gardé le screen dans un coin au cas où.

ECHO : 
- OK : echo " bonjour " ==> attendu: - bonjour -, obtenu -bonjour-
- (90 : OK) echo $ ==> attendu: $, obtenu: (empty)
- (92 : OK) echo $?$ ==> attendu: 0$, obtenu: 0
- (99 : OK) echo login is [$USER] ==> 
    attendu: login is [lmurtin]
    obtenu: login is [
- (101 : OK) echo non existing variable [$TOTO] ==> 
    attendu: non existing variable []
    obtenu: non existing variable [
- (104 : OK) echo $9HOME ==> attendu: HOME, obtenu: (empty)
- (105 : OK) echo $HOME% ==> attendu: /mnt/nfs/homes/lmurtin%
                        obtenu: (empty)
- (131 : OK) echo "$""" ==> attendu: $, obtenu: (empty)
- (133/135 : OK) echo $"HOME" et echo $""HOME et echo $''HOME ==> 
    attendu: HOME, obtenu: (empty)
- (143 : OK) echo ''$HOME ==> attendu: /mnt/nfs/homes/lmurtin
                    obtenu: $HOME
- (145 à 151 : OK) echo $ suivi de diverse combinaisons de lettres et quotes => obtenu: (empty) pour diverses attendus

EXPORT :
- (218 : OK a reverifier avec toi) export "" ==> attendu: "Not a valid identifier"
                        obtenu: "Too few arguments" (la commande export ne recoit pas la chaine vide en tant qu'argument)
- (267 : OK) export TEST$USER=bonjour (+ env) ==>
    attendu: TESTlmurtin=bonjour
    obtenu: TEST
- (272 + 280 : OK) même pb que précédent: export $USER=bonjour (+env) ==>
    attendu: lmurtin=bonjour
    obtenu: "Too few arguments" (cause probable : l'expander ne s'arrête pas au `=`)
- (274 : OK) export TEST="       -n bonjour     " (+ echo $TEST) ==>
    attendu: bonjourminishell>
    obtenu: "Invalid option" (export recoit séparément le contenu entre double quotes)
- (275 : OK) export HOLA="bonjour   "/ (+ echo $HOLA) ==>
    attendu: bonjour /
    obtenu: "/ not a valid identifier"
- (276 : OK a reverifier avec toi) export TEST='"' (+ echo " $TEST ") ==>
    attendu:  " (avec espace avant et après)
    obtenu: (empty) (variable TEST bien set à " mais impossible de l'afficher)
- (278 : OK a reverifier avec toi) export "" TEST=test ==>
    attendu: " '"' not a valid identifier" + TEST=test
    obtenu: TEST=test (export recoit une chaine vide au lieu des quotes et ne détecte donc pas de symbole invalide)
- (310) export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8
        + echo "$A'$B"'$C"$D'$E'"$F'"'$G'$H"
    attendu: 1'2$C"$D5"$F'7'8
    obtenu: 1'23"45"6'7'8
