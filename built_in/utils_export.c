/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:47:00 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/30 11:58:33 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_dest(char *content, char **dest)
{
	dest[0] = ft_strdup(content);
	dest[1] = NULL;
}

int	without_env(t_data *data, int i)
{
	char	**var;

	var = ft_split(data->cmd_arg[i], '=');
	if (chek_nonvalid_var(var[0]) == 0
		||ft_compare(var[0], "_") == 1 || ft_compare(var[0], "PWD")
		|| ft_compare(var[0], "VALGRIND_LIB")
		|| ft_compare(var[0], "LD_PRELOAD"))
	{
		free_tab(var);
		return (0);
	}
	free_tab(var);
	return (1);
}
