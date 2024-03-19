/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_exit_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:55:36 by nrea              #+#    #+#             */
/*   Updated: 2024/03/19 13:57:33 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"

/*Return the exit status value in the form of an int
 for testing during execution*/
int	ft_get_exit_status(t_svars *svars)
{
	return (ft_atoi(svars->exit_code));
}

static int	ft_allocate(char **var)
{
	*var = malloc(4 * sizeof(char));
	if (!*var)
		return (0);
	ft_memset(*var, 0, 4 * sizeof(char));
	return (1);
}

/*Set the exit code value as a char* from an int value between 0 and 255 */
int	ft_set_exit_status(int status, t_svars *svars)
{
	char	*var;
	int		division_value;
	int		temp;
	int		i;

	if (status < 0 || status > 255 || !ft_allocate(&var))
		return (0);
	division_value = 1;
	temp = status;
	while (temp >= 10)
	{
		temp /= 10;
		division_value *= 10;
	}
	i = 0;
	while (division_value >= 1)
	{
		var[i] = status / division_value + '0';
		status %= division_value;
		division_value /= 10;
		i++;
	}
	free(svars->exit_code);
	svars->exit_code = var;
	return (1);
}
