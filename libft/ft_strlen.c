/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:44:21 by sdeutsch          #+#    #+#             */
/*   Updated: 2023/11/16 16:27:43 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	printf("%zu\n", ft_strlen("hello"));
// 	printf("%zu\n", strlen("hello"));
// 	printf("%zu\n", ft_strlen(" "));
// 	printf("%zu\n", strlen(" "));
// 	printf("%zu\n", ft_strlen(""));
// 	printf("%zu\n", strlen(""));
// 	return (0);
// }