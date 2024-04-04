[33mcommit 27fc3fe2f9362a19920cc374284925abf13a075b[m[33m ([m[1;36mHEAD -> [m[1;32mmain[m[33m)[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Tue Apr 2 16:35:02 2024 +0200

    Pathname expansion work in progress

[33mcommit 4a58dde91b9fe9898a0ccfc5685d97494f2a8063[m[33m ([m[1;31morigin/main[m[33m, [m[1;31morigin/HEAD[m[33m)[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Mon Apr 1 18:55:57 2024 +0200

    Expand pthname...work in progress

[33mcommit 8d463fd5f3d37c0bb4a6686b43dfb7a271bfadb2[m
Author: Nicolas Rea <nrea@paul-f5Br1s2.clusters.42paris.fr>
Date:   Fri Mar 29 17:51:35 2024 +0100

    correction funcheck

[33mcommit fa829baab883fd6b09f9ace2e0077ce5b222085f[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Fri Mar 29 13:50:22 2024 +0100

    Remove main

[33mcommit e2b7448a94c3587b5761004120a8d278ff4d6d41[m
Merge: 30fc24a d7661db
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Fri Mar 29 13:45:50 2024 +0100

    Merge branch 'expansion'

[33mcommit 30fc24a5e1ca44cc6e925ad35371ac558bf34be6[m
Merge: 7a232fa 314678c
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Fri Mar 29 13:45:17 2024 +0100

    Merge branch 'main' of github.com:NicolasReaItalo/minishell

[33mcommit d7661db3ad52144b6f5f67a3ff5d3c6b7ed3eb85[m[33m ([m[1;32mexpansion[m[33m)[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Fri Mar 29 13:44:37 2024 +0100

    MaJ Protection des mallocs

[33mcommit 314678c01bfc841bfca11cb054122021e6144216[m
Author: Nicolas Rea <nrea@paul-f5Br1s2.clusters.42paris.fr>
Date:   Fri Mar 29 12:59:05 2024 +0100

    ajout de petits test pour l'execution

[33mcommit 2951f8ce55fb4d7f8ad328f1d5a3aeb0e2634aee[m[33m ([m[1;31morigin/expansion[m[33m)[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Thu Mar 28 16:04:12 2024 +0100

    Implement pathname expansion

[33mcommit 7a232fa64dfcfe90c101074831b3306886352d10[m
Merge: af1765c 8a808a2
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Thu Mar 28 15:04:15 2024 +0100

    Merge branch 'main' of github.com:NicolasReaItalo/minishell

[33mcommit af1765cd8ef41aad8aa2a0d549118f550646cbee[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Wed Mar 27 16:34:42 2024 +0100

    IFS done and cleaned

[33mcommit 8a808a21356698e6c7a7e7c51a6a76afe3bb9c9e[m
Merge: 9c0f24c 00776aa
Author: Nicolas Rea <nrea@paul-f5Br1s3.clusters.42paris.fr>
Date:   Wed Mar 27 15:53:42 2024 +0100

    Merge branch 'main' into correction_fetch_env_vars

[33mcommit 9c0f24c385da9da17b1fe198fbc352bf33456394[m
Author: Nicolas Rea <nrea@paul-f5Br1s3.clusters.42paris.fr>
Date:   Wed Mar 27 15:40:03 2024 +0100

    Correction de fetch_env_vars
    
    la fonction originale utilisait un split('=') sur la variable d'environnement recue
    pour separer key et value.
    Cela ne marche pas pour une variable contenant plusieurs '=' comme LS_COLORS
    Remplce par une fonction ft_separate_equl qui splitte la chaine autour du premier =

[33mcommit 00776aafe122f20114e1b2a5b7e70b25bf58e4ca[m
Merge: d3f8531 13321ab
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Wed Mar 27 15:12:27 2024 +0100

    Merge branch 'main' of github.com:NicolasReaItalo/minishell

[33mcommit d3f8531eba3f34969a445fddd6de7852f5515bb2[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Wed Mar 27 15:09:01 2024 +0100

    IFS implemented. Cleaning in progress

[33mcommit 13321ab93455606690f827583e29b84901fca5c1[m
Author: Nicolas Rea <nrea@paul-f5Br1s3.clusters.42paris.fr>
Date:   Wed Mar 27 14:16:32 2024 +0100

    Simplification de l'execution
    
    les nodes pipes ne s'executent plus dans des sous-processus
    le type de retouur de exec_root et exec_pipe passe de void a int
    un retour de -1 signifiant une erreur interne : malloc, fork, pipe, dup2 etc...

[33mcommit c952b4929fd181c0b4bfd6493a785071db3fe441[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Tue Mar 26 15:39:51 2024 +0100

    expansion...work in progress

[33mcommit 46be97ac381a26cf2110d0a7e0ee0b16e4a845dd[m
Merge: 8996ca9 b917818
Author: Nicolas Rea <nrea@paul-f5Br3s5.clusters.42paris.fr>
Date:   Tue Mar 26 15:00:34 2024 +0100

    Merge branch 'execution'

[33mcommit b917818e585a44327959495f6cf226aa7e246a12[m[33m ([m[1;31morigin/execution[m[33m)[m
Author: Nicolas Rea <nrea@paul-f5Br3s5.clusters.42paris.fr>
Date:   Tue Mar 26 14:37:40 2024 +0100

    Execution fonctionelle
    
    Il restera a faire :
    - l'expansion totale du node exec dans ft_exec_root
    - la gestion des builtin dans exec_root et exec_pipe

[33mcommit 3ee8fe5ea9bac4f991d3fbbf9f239f639a9b9b33[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 25 19:19:56 2024 +0100

    On commence a separer les fonctions
    
    Il y a un souci de pointeur a regler dans ft_look_for_cmd
    (question du double pointeur char **  vers fullcmd)

[33mcommit 8996ca995105b7f743d0f87816f4ce76dbdedf76[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Mon Mar 25 17:21:54 2024 +0100

    implementation IFS work in progress

[33mcommit de50809cb35ee1a7beac059aed6f58816b7cd656[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 25 14:19:14 2024 +0100

    Fix  ft_capture_here_doc
    
    reecriture de capture here-doc en utilisant get_next_line a la place
    de readline

[33mcommit 6c3e591938c9a51447be9396a8db6fa73d6f95be[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 25 13:19:47 2024 +0100

    remplacement gnl + ajout ft_strcpy

[33mcommit 19d41cff65a3c94fb33434f0d903b3c5a3d85276[m
Merge: a97d1b9 20bc659
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 25 11:30:06 2024 +0100

    Merge branch 'main' into execution

[33mcommit a97d1b99eedf6caa831a37672332907d2a2801bc[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 25 11:14:58 2024 +0100

    redirection des here_doc est fonctionelle
    
    creation d'un fichier temporaire avec un nom unique dans /tmp et redirection

[33mcommit 20bc659331bc372bce19ad3eb7d759b50a9656b3[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Fri Mar 22 17:49:04 2024 +0100

    Implement IFS...work in progress

[33mcommit caa6c02d13d15d27759efdc23352d2942956fc82[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Thu Mar 21 17:21:55 2024 +0100

    expansion...phase implementation IFS...work in progress

[33mcommit a624a4f72da7eb73f98904b07d56f0ce14c6136e[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Thu Mar 21 16:46:48 2024 +0100

    gestion heredoc WIP
    
    il faut fix la generation de noms uniques pour les heredocs

[33mcommit f81539778ef4166b3e23e8725893c22ca269fc19[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Thu Mar 21 15:32:13 2024 +0100

    correction capture_heedoc
    
    correction de l fontion qui oubliait le dernier retour a la ligne

[33mcommit 265cf0ce3fa4c13cc5a8b305b7b4da53909c48b2[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Thu Mar 21 13:23:48 2024 +0100

    Fonction ft_exec : moteur d'execution en place
    
    le moteur d'execution est en place avec la recherche de path,
    l'execution via execve et la gestion des erreurs.
    
    Celle ci est loin d'etre a la norme, il va y avoir une reflxion a faire...

[33mcommit fedcde41eaaf44c3dd7ea8baef4d93e7e7a0b672[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Wed Mar 20 17:18:40 2024 +0100

    Gestion param d'expansion...work in progress

[33mcommit f081e59c691f49b4bed3a8b0c8e31c2a19d74b0c[m
Author: Nicolas Rea <nrea@paul-f5Br5s1.clusters.42paris.fr>
Date:   Wed Mar 20 15:46:45 2024 +0100

    modification de ft_push_env_vars
    
    moodification du prototype de la fonction aafin de pouvoir detecter
    via la valeur de retouur si un pb de malloc a eu lieu

[33mcommit 1fa4890dc923ef652908989c07982cc14e2be484[m
Author: Nicolas Rea <nrea@paul-f5Br5s1.clusters.42paris.fr>
Date:   Wed Mar 20 14:55:01 2024 +0100

    mise en place de l'execution
    
    pour l'instant l'execution est minimale
    on ne peut gerer qu'un node exec sans redirection ni recherche de commandes

[33mcommit b351aec2e00bcff3e65499b615ff79605b829148[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Tue Mar 19 20:08:29 2024 +0100

    Gestion parametres d'expansion...Work in progress

[33mcommit 7337b16e13d9d63504cdeae201220a68d8f32f79[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Tue Mar 19 14:02:07 2024 +0100

    Ajout des fonctions pour gerer l'exit status

[33mcommit d39f7386634a915eae683d21848b214de25e4e76[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Tue Mar 19 11:43:29 2024 +0100

    ENV VARIABLES : norminette ok

[33mcommit 6011815ccf5ae1ca0c1496857e0d9fb2494d4dbd[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Tue Mar 19 11:04:13 2024 +0100

    ajout set_var et append var version variables speicales shell

[33mcommit ed7f0dd8872a1370c09cea7d9f04adb1ae550f5f[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 18 18:55:16 2024 +0100

    Gestion des variables speciales
    
    modification de ft_get_var_value pour gerer les variables speciales $? et $IFS
    les fonctions d'initialisations et de free ont aussi ete modifiees
    cf test/test_env_variables.c pour un exemple

[33mcommit c9f2ab440ffb603680339295a34e4169ebef4f33[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 18 18:01:22 2024 +0100

    separation des fichiers de env_vars et creaton d'un fichier dedie

[33mcommit 08a46f72cb97699846cfca72ee88e2e1b30178d3[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 18 17:28:01 2024 +0100

    Ajout fonction append_var qui sera utile pour la creation du builtin export
    
    ft_append(key, value)
    ajoute la value a la fin de la variable identifiee par key au lieu de la remplacer

[33mcommit 4a921e48d0676308ea59090c1b5d7fbab41d8015[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 18 16:58:24 2024 +0100

    push_env_vars terminee norminette ok
    
    TODO
    
        longueur ft_put_env_vars
        separer lefichier env_variables.c en plusieurs fichers
        gestion des variables speciales $? $IFS
        gestion IFS
    
        fonction append -> export avec l'option +=

[33mcommit b99443dedf9ec505f4ad42300df2c6af35df0436[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 18 16:43:18 2024 +0100

    ft_push_env_vars fonctionnelle
    
    TODO
    
    longueur ft_put_env_vars
    separer lefichier env_variables.c en plusieurs fichers
    gestion des variables speciales $? $IFS
    gestion IFS
    
    fonction append -> export avec l'option +=

[33mcommit 00af4c733fa3d4c26582461741de2173afec26ba[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 18 14:33:57 2024 +0100

    Ajout de ft_strcmp dans la libft

[33mcommit 83d2314a791d2d3f1d58376e01053178a905da37[m
Merge: 5b65b36 13a67d4
Author: NicolasReaItalo <75336596+NicolasReaItalo@users.noreply.github.com>
Date:   Mon Mar 18 14:04:04 2024 +0100

    Merge pull request #13 from NicolasReaItalo/env_var
    
    Variables d'environnement : squelette fonctionnel

[33mcommit 13a67d4714f6ff92730b097a91b432d0d908f9cd[m[33m ([m[1;31morigin/env_var[m[33m)[m
Merge: 4bf48b5 5b65b36
Author: NicolasReaItalo <75336596+NicolasReaItalo@users.noreply.github.com>
Date:   Mon Mar 18 14:03:33 2024 +0100

    Merge branch 'main' into env_var

[33mcommit 4bf48b5870dde15cbbdfd976ae17b13c6455cf09[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 18 14:00:27 2024 +0100

    variables d'environnement
    
    reste a faire:
    
    push_env_vars
    expansion
    nettoyage + norminette

[33mcommit 6b1a2e38f2a17682e275e68218f06c644cdc339e[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 18 12:01:26 2024 +0100

    wip

[33mcommit 8570b7845a8f88039d9991446728e950677174b8[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 18 10:04:01 2024 +0100

    correction de ft_unset
    
    jeu de pointeur mal attribue quand prev != NULL.

[33mcommit 5b65b36fb9caa55501ae4da2d646de8583ee0172[m[33m ([m[1;31morigin/correct_token[m[33m, [m[1;32mcorrect_token[m[33m)[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Sat Mar 16 18:07:11 2024 +0100

    Tokenisation operationnel
    
    tokenisation seems to work well and has been normalised
    Other tests are welcomed.

[33mcommit a93e2ffc66b6a5e73bde5b7b48ee40b358ace4cd[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Sat Mar 16 17:05:01 2024 +0100

    Correction of tokenisation_norminette to do

[33mcommit 97fab18c5535b2ded1a4b074cf7805b22d258ed3[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Fri Mar 15 19:44:37 2024 +0100

    Gestion des variables fonctionelles
    
    A FAIRE
    ft_unset(key) => reduire le nb de lignes
    faire ft_ var to splitted -> pour passer a execve
    expand() avec le field splitting
    variables speciales $? etc...

[33mcommit 0b136d969b6a94515d84682020c0cc5c097f763f[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Fri Mar 15 17:38:33 2024 +0100

    modification error with simple quotes

[33mcommit 082ec1ded614a2c8268ae6bd44ebd17e1723ff9c[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Wed Mar 13 18:43:20 2024 +0100

    correction of tokenisation

[33mcommit 129afbac11ac6e8571912e8ee967c5e5fc1d1654[m
Merge: 3c5ea25 649de2f
Author: NicolasReaItalo <75336596+NicolasReaItalo@users.noreply.github.com>
Date:   Wed Mar 13 13:39:25 2024 +0100

    Merge pull request #12 from NicolasReaItalo/ft_dprintf
    
    Ft dprintf

[33mcommit 649de2f9db0bc0b35fd85f90104e7dabf7fd0dd3[m[33m ([m[1;31morigin/ft_dprintf[m[33m)[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Wed Mar 13 13:37:37 2024 +0100

    suppression du fichier de tests

[33mcommit 7b09e2e9ce336020ce927ff751620318cd9158d7[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Wed Mar 13 13:34:10 2024 +0100

    transformation de ft_printf en ft_dprintf dans libft
    
    ft_dprintf prend unparametre fd (file descriptor) en plus
    afin de pouvoir ecrire sur le canal d'erreurs

[33mcommit 3c5ea25305b364ecd89696d96017e3fe088c3c15[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Tue Mar 12 16:54:56 2024 +0100

    Change value of & to be a word

[33mcommit ee8e71ffc2bc3c1f84cafc1bcca0392d6f9ca3b5[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Tue Mar 12 16:09:05 2024 +0100

    suppression build_done

[33mcommit 38360acc27b1eb2e93c62d6109580f111adbb358[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Tue Mar 12 16:06:16 2024 +0100

    ajout .build_done dans .gitignore

[33mcommit c6b8b718a8142b82fbe0bd1fafb2587226d46b82[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Tue Mar 12 16:03:37 2024 +0100

    suppression binaire test_parse_tree

[33mcommit b30a84d497bf64bdbe874489945e948c348e9d4f[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Tue Mar 12 16:02:41 2024 +0100

    parse_tree_nodes.c => ajout des memset
    
    Ajout des memsetpour l'initialisation des nodes de l'arbre

[33mcommit 1eafe4b8e930bf922ac8e59047d277a8bbfc3dde[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Tue Mar 12 16:00:39 2024 +0100

    correction typo node->bultin devient node->builtin

[33mcommit 71906e8bfb8f990aa969acf09cd750e45552df2e[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Tue Mar 12 15:59:57 2024 +0100

    Ajout elements .gitignore

[33mcommit b8eb11ddf932356555bcc3e646d993db2b545318[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Tue Mar 12 15:50:16 2024 +0100

    Correct initialisation in new_token
    
    the new token was malloc but the ptr inside the structure weren't initialised.
    The solution, which seems a good practice, was to use "ft_memset"

[33mcommit 2867fc664888f166e5a2acab53b57030cf61c85d[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Tue Mar 12 14:45:00 2024 +0100

    tests affiche arbre

[33mcommit fe0f58f705016fecabb743bf2ab054475ea04c5d[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Tue Mar 12 14:40:43 2024 +0100

    add parsing tests + modification of tester

[33mcommit 7141ae6631fd97ba08edef275aca2b8d1bec834d[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Tue Mar 12 11:37:28 2024 +0100

    Correct errors in bracket

[33mcommit 87d3139529073b8190762a81fbe67b441791102c[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Tue Mar 12 11:32:02 2024 +0100

    Add few test + color on tester

[33mcommit d0b1c17fa4244850fb7baf889c12ba1d1908ba83[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Mon Mar 11 16:58:41 2024 +0100

    Maj makefile + testeur fonctionnel

[33mcommit 544dbc361de046c22eefdb6d00a0b718293da421[m
Merge: db16bb1 4703a22
Author: NicolasReaItalo <75336596+NicolasReaItalo@users.noreply.github.com>
Date:   Mon Mar 11 16:14:58 2024 +0100

    Merge pull request #10 from NicolasReaItalo/main_parsing-complet
    
    Main parsing complet

[33mcommit 4703a22dfa85411ca601615e1166ca75f4b25fb3[m[33m ([m[1;31morigin/main_parsing-complet[m[33m)[m
Merge: 09aada5 db16bb1
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 11 16:14:15 2024 +0100

    Merge branch 'main' into main_parsing-complet

[33mcommit 09aada5fb0c46c64454e1d8c421ccd01d8e2196c[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 11 16:12:29 2024 +0100

    Main fonctionnel

[33mcommit db16bb1c5e56bac522da064187a16148db32f463[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Mon Mar 11 16:11:16 2024 +0100

    implement test parsing...Work in progress

[33mcommit 412a98865495ed055ed72c999dc0448bcdb8380d[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 11 14:47:38 2024 +0100

    suppression show_tree en doublon dans minishell.c

[33mcommit a26d7f27c9630250203c2de1f1500011520e76b3[m
Merge: 0e2801b 51233b6
Author: NicolasReaItalo <75336596+NicolasReaItalo@users.noreply.github.com>
Date:   Mon Mar 11 14:37:55 2024 +0100

    Merge pull request #8 from NicolasReaItalo/parse_tree
    
    Parse tree

[33mcommit 51233b6adef2fb15732e908f08d1efff2b1aceed[m[33m ([m[1;31morigin/parse_tree[m[33m)[m
Merge: c4021d4 0e2801b
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 11 14:30:07 2024 +0100

    Merge branch 'main' into parse_tree

[33mcommit c4021d4b694fd679be33317f97f11cd1aeb65ec5[m
Author: Nicolas Rea <nrea@paul-f5Br6s3.clusters.42paris.fr>
Date:   Mon Mar 11 14:21:44 2024 +0100

    Parse_tree termine
    
    norminette OK.
    
    Plus qu'a rediger les tests...

[33mcommit 32430ee0b452f2b2068989a23e4f1727325c5261[m[33m ([m[1;32mparse_tree[m[33m)[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 18:59:40 2024 +0100

    Ca marche !
    
    Ca a l'air de bien marcher,
    
    maintenant il faut tester tout ensemble avec tous les cas de figures possibles et
    ameliorer l'affichage.

[33mcommit ec646842820fcf77e4f994c7d85ded4b859b37ad[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 18:18:52 2024 +0100

    cmd de compilation du test

[33mcommit 71ec51639cb250b510c9271f9706fc580d347f79[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 18:17:18 2024 +0100

    pourquoi les cmd n'apparaissent pas? Mystere...

[33mcommit 0e2801b3a2d52fd5ef940059f63394d255c62050[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Fri Mar 8 17:47:19 2024 +0100

    Add Show_tree

[33mcommit b917d91d34f1325172133f3a86e378becea6d3c4[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 17:46:36 2024 +0100

    parsing en cours
    
    Quasiment fini plus qu'a tester et debugger....

[33mcommit f3ec2845ffc84bd4bd3674a25d840e42bf3c71a9[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Fri Mar 8 16:57:18 2024 +0100

    Add Makefile

[33mcommit a3db8830e989a4fa269ec04cf76ecaaf2f4b26b8[m
Merge: cfde6f7 bc83169
Author: NicolasReaItalo <75336596+NicolasReaItalo@users.noreply.github.com>
Date:   Fri Mar 8 16:22:10 2024 +0100

    Merge pull request #7 from NicolasReaItalo/parser
    
    parsing en cours

[33mcommit bc831693a23afe57d8d4f31e4b64525c72a2ed72[m[33m ([m[1;31morigin/parser[m[33m)[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 16:21:00 2024 +0100

    parsing en cours
    
    les fonctions autres que celles de parser.c sont testees et a la norme

[33mcommit cfde6f7cfdf502e2076fb4b53fbae898ee74fe98[m
Merge: 82c3b9d 66359aa
Author: NicolasReaItalo <75336596+NicolasReaItalo@users.noreply.github.com>
Date:   Fri Mar 8 14:29:27 2024 +0100

    Merge pull request #6 from NicolasReaItalo/nettoyage_token
    
    Nettoyage token

[33mcommit 66359aa318ef7ce7236c642b664df587dbb58d93[m[33m ([m[1;31morigin/nettoyage_token[m[33m)[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 14:26:36 2024 +0100

    correction variable inutile dans test_redirections

[33mcommit 2b354504cb0d97cb6d35274829cc78c55cfd7440[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 14:21:05 2024 +0100

    nettoyage des fonctions doublons dans token.c et token_utils.c
    
    certaines ont ete deplacees dans test/utils
    ajout du test de redirections

[33mcommit 82c3b9d5250b6d861a6f95f059ae23eebb0c829a[m
Merge: ed9b3f8 ee49cee
Author: NicolasReaItalo <75336596+NicolasReaItalo@users.noreply.github.com>
Date:   Fri Mar 8 13:38:21 2024 +0100

    Merge pull request #5 from NicolasReaItalo/redirections
    
    Redirections

[33mcommit ee49cee374e5f221cf10d87d053f4f600bcee789[m[33m ([m[1;31morigin/redirections[m[33m)[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 13:35:15 2024 +0100

    raz des fichiers externes modifies pour merge simple

[33mcommit 9014b45fe02af21acb4db6e41803d1ee7b29ab8b[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 13:32:47 2024 +0100

    Tout est a sa place prete a merger sur main
    
    il restera a mettre en place le tst dans une autre branche

[33mcommit c93c1a6aab7e9a2db20ac2767e9af6f4f8a7b854[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 13:15:14 2024 +0100

    ajout here doc.c au repertoir srcs

[33mcommit 5ca04d5e58425128e22647c0cba45a2903a5e26c[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 13:12:04 2024 +0100

    mise en repertoires

[33mcommit 160d7fd0653d857d75190fec92fd5185d9676276[m
Merge: 1597d26 ed9b3f8
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 13:08:10 2024 +0100

    Merge branch 'main' into redirections

[33mcommit ed9b3f857f2672d322b09ed451aaf0eec48db168[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Fri Mar 8 13:07:02 2024 +0100

    Create directories

[33mcommit 1597d269102415b98af70b6cfa7648841119e6ec[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 13:05:39 2024 +0100

    nettoyage et repartitien
    
    repartitiion entre here_doc.c et redirections.c

[33mcommit 081b0ccad66bdc5947e7f63cc2f4b25e4c997b25[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 8 11:26:19 2024 +0100

    redirection et clean fonctionnnels
    
    il reste du travail pour la norminette et placer descommandes de testes dans les =bons fichiers

[33mcommit 828350537bd024a41cc840b6ca4a652c9e7eaa63[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Thu Mar 7 18:34:05 2024 +0100

    premier jet redirections
    
    la fonction clean_words est broken !

[33mcommit a309d8edbf5c60a77b3fd08c722e7d43062962b6[m
Merge: 0493579 2e0fd99
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Thu Mar 7 15:28:23 2024 +0100

    Merge branch 'main' into parser

[33mcommit 2e0fd9952fa44448845e574286a41e49b210b542[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Thu Mar 7 13:32:21 2024 +0100

    Correct leak of check_syntax

[33mcommit 23add77fd7db7f7f6f22d7104e37b1c7cd437471[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Tue Mar 5 16:31:38 2024 +0100

    Add check_syntax ... to check and normalize

[33mcommit 4629094d37f69b6852e4111c3ddb4dd7eb44ca12[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Mon Mar 4 17:41:45 2024 +0100

    check_syntax work in progress

[33mcommit 0531d8c12928fa638b6fd85e41ecfdef8ca7e237[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 1 16:48:55 2024 +0100

    Ajout de la fonction reverse_stack

[33mcommit 04935793857b97c2e0865f3c462a12e47337cf1f[m
Merge: 60ee62e 7284c37
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 1 16:26:04 2024 +0100

    Merge branch 'main' into parser

[33mcommit 7284c37ba57142d9ea7f323bdba531722f8949f5[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 1 16:24:55 2024 +0100

    Ajout de token_utils
    
    petits utilitaires de gestion  des token qui serviont dans parser et check_syntaxe

[33mcommit 60ee62e8445659b5fc1b58e28e9f1b7943a948bd[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 1 16:22:58 2024 +0100

    remove de token_utils pour les merger depuis une autre branche

[33mcommit 7c6957a3187b77f67cb2af7ca855ce21335667c0[m
Merge: e215d25 bafeb73
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 1 16:16:16 2024 +0100

    Merge branch 'main' into parser

[33mcommit e215d25d4a17d81384cbbe75d2dfea43ebe64279[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 1 16:14:34 2024 +0100

    nettoyage et mise a niveau

[33mcommit 8e53c53cac424db8094ad606610bb474a56e282f[m
Merge: d26944e 147ad0d
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Fri Mar 1 15:58:04 2024 +0100

    Merge branch 'main' into parser

[33mcommit d26944ebd7265b085fb12ca67fa4d7d068ae2169[m
Author: Nicolas Rea <nrea@paul-f5Br5s3.clusters.42paris.fr>
Date:   Thu Feb 29 16:40:29 2024 +0100

    parsing en cours
    
    Pas mal avance
    
    Reste la fonction ft_exec_node a terminer avec surtout le
    dispatch entre les stacks et la verification de la bonne alternance op word

[33mcommit bafeb7346f2fcfe578f19f945a589a2f93df090b[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Thu Feb 29 16:33:52 2024 +0100

    Done tokenisation ...implement check_syntax

[33mcommit 875e295185e99a157a3781d5d946a4ca776be05d[m
Author: Nicolas Rea <nrea@paul-f5Br6s1.clusters.42paris.fr>
Date:   Wed Feb 28 17:44:18 2024 +0100

    debut du parser

[33mcommit 147ad0df7627fd03bb8c728ce9a94c3b2532b351[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Wed Feb 28 17:04:09 2024 +0100

    Tokenisation...work in progress

[33mcommit c9eb564c1a0586b371650bda8967009848c505ba[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Tue Feb 27 18:31:25 2024 +0100

    Implementing Tokeniser - To debug
    
    Pas eu le temps debugger... Work in progress

[33mcommit 04d6684d7bcc68c8cccb3041a7d961875caac36c[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Tue Feb 27 15:20:21 2024 +0100

    Add token.h

[33mcommit ae5f81dd1ad2e21240a74556a260c4e88eaa8134[m
Author: tomjoy75 <tomjoy75@gmail.com>
Date:   Thu Feb 22 16:50:49 2024 +0100

    Ajout du sujet

[33mcommit 18e7739e987c5575ce29dfd1669ca13f5cd1461a[m
Author: NicolasReaItalo <75336596+NicolasReaItalo@users.noreply.github.com>
Date:   Thu Feb 22 11:30:59 2024 +0100

    Update README.md

[33mcommit 3e1a1816cc383a82ed0b18101392bb530a0e1951[m
Author: NicolasReaItalo <75336596+NicolasReaItalo@users.noreply.github.com>
Date:   Thu Feb 22 11:29:37 2024 +0100

    Update README.md

[33mcommit ba8d82a5b11ee2481fc52ba565b4d18485118c5e[m
Author: NicolasReaItalo <75336596+NicolasReaItalo@users.noreply.github.com>
Date:   Thu Feb 22 11:25:18 2024 +0100

    Initial commit
