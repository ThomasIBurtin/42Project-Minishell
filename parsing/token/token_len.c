/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:53:15 by transfo           #+#    #+#             */
/*   Updated: 2024/04/25 17:57:18 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// len d'une variable
int	len_variable(char *str, int *i, t_programme *programme)
{
	char	*cle;
	char	**env_value;
	char	**variable_value;
	int		len;

	len = 0;
	cle = extracte_cle(str, i);
	env_value = find_value(*programme->envp, cle);
	variable_value = find_value(*programme->liste_variable, cle);
	if (env_value != NULL)
		len = ft_strlen(env_value[1]);
	else if (variable_value != NULL)
		len = ft_strlen(variable_value[1]);
	if (variable_value != NULL)
		free_tab(variable_value);
	if (env_value != NULL)
		free_tab(env_value);
	free(cle);
	return (len);
}

//len tant auon est dans les doubles quotes
int	len_in_doublequotes(char *str, int *i, t_programme *programme)
{
	int		len;
	char	*convert;

	len = 0;
	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		convert = ft_itoa(g_exitstatus);
		len = ft_strlen(convert);
		*i += 2;
		free(convert);
	}
	else if (str[*i] == '$' && str[*i + 1] && str[*i + 1] != 34)
		len = len_variable(str, i, programme);
	else
	{
		len++;
		*i += 1;
	}
	return (len);
}

// calculer la len de de la commande avec les variable
int	len_commande(char *str, t_programme *programme)
{
	int (i) = 0;
	int (len) = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] != 34)
				len += len_in_doublequotes(str, &i, programme);
			i++;
		}
		else if (str[i] == 39)
		{
			i += 1;
			while (str[i] != 39)
			{
				len += 1;
				i += 1;
			}
			i += 1;
		}
		else
			len += len_in_doublequotes(str, &i, programme);
	}
	return (len);
}

// extraire la cle de la varieble ex $toto la cle est toto
char	*extracte_cle(char *str, int *i)
{
	int		compteur;
	int		save;
	int		j;
	char	*result;

	*i += 1;
	save = *i;
	compteur = 0;
	j = 0;
	while (str[*i] && str[*i] != ' ' && str[*i] != 34 && str[*i] != 39
		&& str[*i] != '$' && str[*i] != ':')
	{
		*i += 1;
		compteur++;
	}
	result = (char *)malloc(sizeof(char) * compteur + 1);
	while (str[save] && str[save] != ' ' && str[save] != 34 && str[save] != 39
		&& str[save] != '$' && str[save] != ':')
		result[j++] = str[save++];
	result[j] = '\0';
	return (result);
}

void	add_back_front(t_token **liste_token, t_token *new)
{
	t_token	*current;

	if (*liste_token == NULL)
	{
		*liste_token = new;
		(*liste_token)->next = NULL;
	}
	else
	{
		current = *liste_token;
		while (current->next != NULL)
		current = current->next;
		current->next = new;
		new->prev = current;
	}
}
