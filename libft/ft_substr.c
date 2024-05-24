/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:08:01 by sdeutsch          #+#    #+#             */
/*   Updated: 2023/11/17 18:32:11 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			i;
	unsigned int	j;
	size_t			k;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	k = ft_strlen(s + start);
	if (len > k)
		len = k;
	dest = malloc ((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	j = start;
	while (s[j] && i < len)
	{
		dest[i] = s[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char *str = ft_substr("tripouille", 100, 1);
// 	printf("%s\n", str);
// 	free(str);
// 	return (0);
// }
