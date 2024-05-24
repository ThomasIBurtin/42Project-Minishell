/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:05:53 by transfo           #+#    #+#             */
/*   Updated: 2024/04/29 14:40:37 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norminette(t_token *new, t_index *index, char *str)
{
	index->i++;
	while (str[index->i] != 39)
	{
		new->str[index->j] = str[index->i];
		index->j++;
		index->i++;
	}
	index->i++;
}

int	tt(t_token *current)
{
	if (current->next == NULL || current->prev == NULL
		|| current->next->str[0] == '|' || current->next->str[0] == '\0')
		return (0);
	return (1);
}

int	modife_liste(t_token *current, t_type type, t_token **liste_token)
{
	t_token	*temp;

	temp = current;
	if (current->next == NULL || current->next->str[0] == '>'
		|| current->next->str[0] == '<' || current->next->str[0] == '|')
		return (0);
	else if (current->prev == NULL)
	{
		*liste_token = (*liste_token)->next;
		(*liste_token)->type = type;
		(*liste_token)->prev = NULL;
	}
	else
	{
		current = current->prev;
		current->next = temp->next;
		temp->next->prev = current;
		temp->next->type = type;
	}
	free(temp->str);
	free(temp);
	return (1);
}

// attribution des type
int	add_type(t_token *current, t_token **liste_token, int *flag)
{
	int (i) = 1;
	if (current->str[0] == '>' && current->str[1] == '>')
		i = modife_liste(current, append, liste_token);
	else if (current->str[0] == '>')
		i = modife_liste(current, outfile, liste_token);
	else if (current->str[0] == '<' && current->str[1] == '<')
		i = modife_liste(current, here_doc, liste_token);
	else if (current->str[0] == '<')
		i = modife_liste(current, infile, liste_token);
	else if (current->str[0] == '|')
	{
		if (tt(current) == 0)
			return (0);
		current->type = pip;
		*flag = 0;
	}
	else if ((current->prev == NULL || current->prev->type != commande)
		&& *flag == 0)
	{
		current->type = commande;
		*flag = 1;
	}
	else
		current->type = argument;
	return (i);
}

//recuperer le type de l'argument avec l'enumeration
t_type	get_type_arg(t_token **liste_token)
{
	t_token	*current;
	int		flag;

	flag = 0;
	current = *liste_token;
	while (current)
	{
		if (current->type == none)
		{
			if (add_type(current, liste_token, &flag) == 0)
				return (0);
			current = *liste_token;
		}
		else
			current = current->next;
	}
	return (1);
}
