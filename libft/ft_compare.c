/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:28:56 by transfo           #+#    #+#             */
/*   Updated: 2024/03/29 12:16:54 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_compare(char *str, char *strr)
{
	int	i;

	i = 0;
	if (ft_strlen(str) != ft_strlen(strr))
		return (0);
	while (str[i] && strr[i])
	{
		if (str[i] != strr[i])
			return (0);
		i++;
	}
	return (1);
}
