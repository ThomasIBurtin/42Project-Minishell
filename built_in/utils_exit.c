/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:41:15 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/23 17:58:35 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long int	ft_atoll(const char *str)
{
	int				i;
	int				sign;
	long long int	num;

	sign = 1;
	num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if ((str[i + 1] == '-') || (str[i + 1] == '+'))
			return (0);
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * sign);
}

int	check_ll(char *number)
{
	if (ft_strncmp(number, "-", 1) != 0 && ft_strlen(number) > 19)
		return (0);
	else if (ft_strncmp(number, "-", 1) != 0 && ft_atoll(number) < 0)
		return (0);
	else if (ft_strncmp(number, "-", 1) == 0 && ft_atoll(number) > 0)
		return (0);
	return (1);
}
