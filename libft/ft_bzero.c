/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:19:42 by sdeutsch          #+#    #+#             */
/*   Updated: 2023/11/16 16:03:54 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = s;
	i = 0;
	while (i < n)
	{
		tmp[i] = '\0';
		i++;
	}
}

// #include <stdio.h>
// #include <strings.h>

// int	main(void)
// {
// 	char	str[] = "Hello World";
// 	char	str2[] = "Hello World";
// 	printf("%s\n", str);
// 	printf("%s\n", str2);
// 	ft_bzero(str + 2, sizeof(char) *4);
// 	bzero(str2 + 2, sizeof(char)* 4);
// 	printf("%s\n", str);
// 	printf("%s\n", str2);
// 	return (0);
// }