/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:53:32 by transfo           #+#    #+#             */
/*   Updated: 2024/04/26 19:35:54 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// chek si il ne manque pas une quotes
int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] && str[i] != 34)
				i++;
			if (str[i] == '\0')
				return (0);
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
			if (str[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

int	calculate_new_size(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = ft_strlen(s);
	while (s[i])
	{
		if ((s[i] == '>' && s[i +1] == '>') || (s[i] == '<' && s[i +1] == '<'))
		{
			count += 2;
			i++;
		}
		else if (s[i] == '<' || s[i] == '>' || s[i] == '|')
			count += 2;
		i++;
	}
	return (count);
}

void	add_space(char *s, char *result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if ((s[i] == '>' && s[i +1] == '>') || (s[i] == '<' && s[i +1] == '<'))
		{
			result[j++] = ' ';
			result[j++] = s[i++];
			result[j++] = s[i];
			result[j++] = ' ';
		}
		else if (s[i] == '<' || s[i] == '>' || s[i] == '|')
		{
			result[j++] = ' ';
			result[j++] = s[i];
			result[j++] = ' ';
		}
		else
			result[j++] = s[i];
		i++;
	}
	result[j] = '\0';
}

// inserer des espace autour des <, > 
char	*insert_spaces(char *str)
{
	char	*result;

	result = malloc(sizeof(char) * (calculate_new_size(str) + 1));
	add_space(str, result);
	free(str);
	return (result);
}

int	len_new_tab(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i +1] && ((str[i] == 39 && str[i +1] == 39)
					|| (str[i] == 34 && str[i +1] == 34))))
			i++;
		else
			count++;
		i++;
	}
	return (count + 1);
}
