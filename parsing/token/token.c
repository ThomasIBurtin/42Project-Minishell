/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:16:39 by tburtin           #+#    #+#             */
/*   Updated: 2024/04/24 16:54:52 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// trouver la variable de la cle si elle existe
char	**find_value(t_list *list, char *cle)
{
	char	**tab_key_value;

	while (list)
	{
		tab_key_value = ft_split(list->content, '=');
		if (tab_key_value[1] != NULL && ft_compare(tab_key_value[0], cle) == 1)
			return (tab_key_value);
		free_tab(tab_key_value);
		list = list->next;
	}
	return (NULL);
}

// remplacer les cles par les variables
void	input_variable(t_token *new, char *str,
	t_programme *programme, t_index *index)
{
	int		k;
	char	*cle;
	char	**env_value;
	char	**variable_value;

	k = 0;
	cle = extracte_cle(str, &index->i);
	env_value = find_value(*programme->envp, cle);
	variable_value = find_value(*programme->liste_variable, cle);
	if (env_value != NULL)
	{
		while (env_value[1][k])
			new->str[index->j++] = env_value[1][k++];
		free_tab(env_value);
	}
	else if (variable_value != NULL)
	{
		while (variable_value[1][k])
			new->str[index->j++] = variable_value[1][k++];
		free_tab(variable_value);
	}
	free(cle);
}

// ecrire tant que la doucle quotes est pas fini
void	input_indoublequotes(t_token *new, char *str,
	t_programme *programme, t_index *index)
{
	int		k;
	char	*exit_status;

	k = 0;
	if (str[index->i] == '$' && str[index->i + 1] == '?')
	{
		exit_status = ft_itoa(g_exitstatus);
		while (exit_status[k])
			new->str[index->j++] = exit_status[k++];
		index->i += 2;
		free(exit_status);
	}
	else if (str[index->i] == '$' && str[index->i + 1]
		&& str[index->i + 1] != 34)
		input_variable(new, str, programme, index);
	else
		new->str[index->j++] = str[index->i++];
}

// crer le str de la commande, avec les $?, variable et gerer les quotes
void	create_commande(t_token *new, char *str, t_programme *programme)
{
	t_index	index;

	index.i = 0;
	index.j = 0;
	new->str = (char *)malloc(sizeof(char) *(len_commande(str, programme) + 1));
	while (str[index.i])
	{
		if (str[index.i] == 34)
		{
			index.i++;
			while (str[index.i] != 34)
				input_indoublequotes(new, str, programme, &index);
			index.i++;
		}
		else if (str[index.i] == 39)
			norminette(new, &index, str);
		else
			input_indoublequotes(new, str, programme, &index);
	}
	new->str[index.j] = '\0';
}

// creation de token (variable , cmd, arg....)
t_token	*ft_newtoken(char *str, t_programme *programme)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	create_commande(new, str, programme);
	new->type = none;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
