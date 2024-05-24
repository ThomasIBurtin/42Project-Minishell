/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:38:17 by tburtin           #+#    #+#             */
/*   Updated: 2024/04/29 17:44:15 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_t_data(t_data *data)
{
	t_data	*temp;

	while (data != NULL)
	{
		temp = data;
		data = data->next;
		free_tab(temp->cmd_arg);
		free_tab(temp->outfile);
		free_tab(temp->outfile_append);
		free_tab(temp->infile);
		free_tab(temp->heredoc);
		free(temp);
	}
}

void	free_t_token(t_token *token)
{
	t_token	*temp;

	while (token != NULL)
	{
		temp = token;
		token = token->next;
		free(temp->str);
		free(temp);
	}
}

void	free_t_liste(t_list *var)
{
	t_list	*temp;

	while (var != NULL)
	{
		temp = var;
		var = var->next;
		free(temp->content);
		free(temp);
	}
}

void	free_onedata(t_data *data)
{
	free_tab(data->cmd_arg);
	free_tab(data->outfile);
	free_tab(data->outfile_append);
	free_tab(data->infile);
	free_tab(data->heredoc);
	free(data);
}

int	gg(t_data *liste_data)
{
	int	comp;

	comp = 0;
	while (liste_data)
	{
		if (liste_data->heredoc[0] != NULL)
			comp++;
		liste_data = liste_data->next;
	}
	if (comp >= 2)
	{
		unlink(".heredoc.tmp");
		return (0);
	}
	return (1);
}
