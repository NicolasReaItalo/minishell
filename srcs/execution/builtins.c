/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:59:41 by nrea              #+#    #+#             */
/*   Updated: 2024/03/29 13:04:09 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
execute builtin
l'expansion ifs wildcards et dequotes ont ete faits
On applique les redirections de pipes si pipe_nb != -1
On applique ls redirections
On execute la fonction builtin ( le premier token retourne la fonction a executer, les autres les arguments)
On set l'exit status selon le retour de cette commande
si pipe_nb == -1
	On restaure les fds
	dup2(0, STDIN)
	dup2(1, STDOUT)

pointeur de fonction sous la forme
builtin(T_token *cmd)

il faudrait un tableau de fonction [7] et un fonction int get_builtin qui renvoie
l'index de la fonction a utiliser dans le tableau



*/
