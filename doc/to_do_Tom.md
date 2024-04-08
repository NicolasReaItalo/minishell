- [X] **Cas de l'expansion des parametres ou le premier caractere est . (et exclusion sinon)**
- [X] !!! Ne prends pas en compte '.' Pourquoi?
- [X] Pourquoi si VAR='*' , il n'y a pas d'expansion


- [ ] Creer un ifs pour redirection
	- si nb_elem > 1 => `$VAR: ambiguous redirect `(attention a l'expansion de $VAR)
	- si words[0] == "" => `$VAR: ambiguous redirect `
	- sinon, remplacer le content de token par word[0]
- [X] Gerer le cas special de ./*
    - ex: `echo ./*` => `./doc ./h ...  `
- [ ] Mettre les printf au format write (ft_putstr_fd())
- [ ] Gerer le unquotting
