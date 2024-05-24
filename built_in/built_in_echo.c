/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:26:32 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/05/14 14:18:43 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*termine l'execution quand on est dans un child*/
static void	exit_echo(void)
{
	char	*argv[1];
	char	*env[1];

	argv[0] = NULL;
	env[0] = NULL;
	execve("/bin/true", argv, env);
}

/*compte le nbr d'arguments d'une commande*/
int	number_of_args(char **cmd_arg)
{
	int	i;

	i = 1;
	while (cmd_arg[i] != NULL)
		i++;
	return (i);
}

static int	ft_strncmp_for_n(const char *s1)
{
	int		i;

	i = 1;
	if (s1[0] != '-')
		return (1);
	else
	{
		while (s1[i])
		{
			if (s1[i] != 'n')
				return (1);
			i++;
		}
	}
	return (0);
}

/*imprime tous les arguments sauf -n et ses variantes (\n si besoin)*/
void	built_in_echo(t_data data)
{
	int		i;
	int		nbr_args;

	int (flag) = 0;
	nbr_args = number_of_args(data.cmd_arg);
	i = 1;
	if (nbr_args != 1)
	{
		while (i < nbr_args)
		{
			if (ft_strncmp_for_n(data.cmd_arg[i]) || flag == 1)
			{
				flag = 1;
				ft_putstr_fd(data.cmd_arg[i], 1);
				if (i + 1 < nbr_args)
					ft_putstr_fd(" ", 1);
			}
			i++;
		}
	}
	if (nbr_args == 1 || (nbr_args != 1 && ft_strncmp_for_n(data.cmd_arg[1])))
		ft_putstr_fd("\n", 1);
	unlink_if_needed(data);
	if (data.next != NULL && data.next->cmd_arg != NULL)
		exit_echo();
}
