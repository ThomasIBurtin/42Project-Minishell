/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:16:11 by sdeutsch          #+#    #+#             */
/*   Updated: 2023/11/16 20:17:38 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tmp;

	if (size && SIZE_MAX / size < nmemb)
		return (NULL);
	tmp = malloc(nmemb * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, (nmemb * size));
	return (tmp);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s\n", (char *)ft_calloc(5, 4));
// 	printf("%s\n", (char *)calloc(5, 4));
// 	printf("%s\n", (char *)ft_calloc(SIZE_MAX, SIZE_MAX));
// 	printf("%s\n", (char *)calloc(SIZE_MAX, SIZE_MAX));
// }