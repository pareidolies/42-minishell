# 42-minishell

![mini50](https://user-images.githubusercontent.com/96736158/226124203-36537df4-dd8f-481d-9b2f-00160c651c22.png)

## Comment ignorer leaks de readline :

1. Compiler normalement.
2. Au lieu d'appeler `valgrind ./minishell`, il faut exécuter leakscheck.sh.
3. Enjoy :D

## Tutoriel Magic Malloc

* MALLOC : Si tu souhaites effectuer un malloc, cela tient en une ligne (il faut juste indiquer la size) :

node = magic_malloc(MALLOC, sizeof(t_token), NULL);

* ADD : Si tu utilises une fonction de la libft qui malloc qqch (ft_strdup, ft_strjoin), apres avoir utilise la fonction, il faut rajouter une ligne (dans laquelle il faut juste indique l'element en question qui a ete malloc) :

result = ft_substr(str, 0, i);

magic_malloc(ADD, 0, result);

* FREE : Si tu souhaites free un seul element, il faut utiliser cette ligne (par exemple pour free tmp) (en indiquant seulement l'element a free) :

magic_malloc(FREE, 0, tmp);

* QUIT : Si tu souhaites free tout ce que tu as malloc depuis le debut de ton programme et quitter, c'est cette ligne :

magic_malloc(QUIT, 0, NULL);

## Les tests

https://docs.google.com/spreadsheets/d/1fFFHGhm2F-ofMvUcIhZnBonpcASGL8954YFBUODmQy0/edit#gid=0
