- [X] **Cas de l'expansion des parametres ou le premier caractere est . (et exclusion sinon)**
- [X] !!! Ne prends pas en compte '.' Pourquoi?
- [X] Pourquoi si VAR='*' , il n'y a pas d'expansion


- [ ] ~~Creer un ifs pour redirection~~
	- si nb_elem > 1 => `$VAR: ambiguous redirect `(attention a l'expansion de $VAR)
	- si words[0] == "" => `$VAR: ambiguous redirect `
	- sinon, remplacer le content de token par word[0]
- [X] Gerer l'ambiguous redirect au niveau de l'expand param
	- ~~**?? Es ce que la separation se fait avec les whitespaces ou l'IFS ??**~~
	- strip the string from ~~whitespaces~~ ifs
	- si empty => error `$VAR: ambiguous redirect `
	- strchr ~~whitespaces~~ ifs => error
	- si strchr *
    	- count valid_pathnames si > 1 =>error

    	- expand   <--- TO DO

- [X] Gerer le cas special de ./*
    - ex: `echo ./*` => `./doc ./h ...  `
- [X] Mettre les printf au format write (ft_putstr_fd())
- [ ] Gerer le unquotting

MESSAGE APRES VACANCES
!!! Ne marche pas encore completement
```
➜  minishell git:(protection) ✗ ./param_expansion "ls -la *'t_''*'"
--------------------
[EXEC] [cmd : {ls}{-la}{*'t_''*'}][redir : ]
----------After----------
[EXEC] [cmd : {ls}{-la}{*'t_'*}][redir : ]

il devrait sortir *t_* !!!


## A VOIR : Messages generant des erreurs ##
valgrind --leak-check=full ./param_expansion 'hello | |'
