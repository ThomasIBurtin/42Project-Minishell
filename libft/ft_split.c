/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:54:10 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/16 14:29:35 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fonc(const char **str)
{
	if (**str == 34)
	{
		(*str)++;
		while (**str && **str != 34)
			(*str)++;
	}
	if (**str == 39)
	{
		(*str)++;
		while (**str && **str != 39)
			(*str)++;
	}
}

int	count_word(const char *str, char c)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	while (*str)
	{
		fonc(&str);
		if (*str != c && x == 0)
		{
			x = 1;
			count++;
		}
		else if (*str == c)
			x = 0;
		str++;
	}
	return (count);
}

static void	suite_fill_tab(const char **s, char c, size_t *j)
{
	while (**s && **s != c)
	{
		if (**s == 34)
		{
			(*j)++;
			(*s)++;
			while (**s && **s != 34)
			{
				(*s)++;
				(*j)++;
			}
		}
		else if (**s == 39)
		{
			(*j)++;
			(*s)++;
			while (**s && **s != 39)
			{
				(*s)++;
				(*j)++;
			}
		}
		(*j)++;
		(*s)++;
	}
}

char	**ft_fill_tab(const char *s, char **res, char c)
{
	size_t		i;
	size_t		j;
	const char	*start;

	i = 0;
	while (*s)
	{
		j = 0;
		start = s;
		if (*s != c)
		{
			suite_fill_tab(&s, c, &j);
			res[i] = ft_substr(start, 0, j);
			if (!res[i])
				return (free_tab(res));
			i++;
		}
		else
			s++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(const char *s, char c)
{
	char	**res;

	if (!s)
		return (0);
	res = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!res)
		return (0);
	res = ft_fill_tab(s, res, c);
	return (res);
}
