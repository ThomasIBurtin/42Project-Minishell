/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:51:00 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/23 18:00:01 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*actualise g_exitstatus et return*/
static void	get_exit(char *exit_msg, int err_nb, t_data data)
{
	if (exit_msg != NULL)
		printf("%s", exit_msg);
	g_exitstatus = err_nb;
	unlink_if_needed(data);
	return ;
}

/*actualise g_exitstatus et exit*/
static int	ft_exit(char *exit_msg, int err_nb, t_data data)
{
	if (exit_msg != NULL)
		printf("%s", exit_msg);
	g_exitstatus = err_nb;
	unlink_if_needed(data);
	return (1);
}

/*verifie le format du nombre*/
static int	check_if_digit(char *number)
{
	int	i;

	i = 0;
	if (!(((number[i] >= '0') && (number[i] <= '9'))
			|| (number[i] == '-') || (number[i] == '+')))
		return (0);
	i = 1;
	while (number[i])
	{
		if (!((number[i] >= '0') && (number[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

/*converti les chiffres qui sont < 0*/
int	infinite_modulo(int num)
{
	while (num < 0)
		num += 256;
	num = num % 256;
	return (num);
}

/*check format et exit avec le bon status*/
int	built_in_exit(t_data data)
{
	int	nbr_args;
	int	num;

	printf("exit\n");
	nbr_args = number_of_args(data.cmd_arg);
	if (nbr_args == 1)
		return (ft_exit(NULL, 0, data));
	if (check_if_digit(data.cmd_arg[1]) == 0 || check_ll(data.cmd_arg[1]) == 0)
		return (ft_exit("numeric argument required\n", 2, data));
	if (nbr_args > 2)
		get_exit("too many arguments\n", 1, data);
	if (nbr_args == 2)
	{
		if ((ft_atoll(data.cmd_arg[1]) >= 256))
			num = ft_atoll(data.cmd_arg[1]) % 256;
		else if ((ft_atoll(data.cmd_arg[1]) < 0))
		{
			num = ft_atoll(data.cmd_arg[1]);
			num = infinite_modulo(num);
		}
		else
			num = ft_atoll(data.cmd_arg[1]);
		return (ft_exit(NULL, num, data));
	}
	return (0);
}
