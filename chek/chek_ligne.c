/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_ligne.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:38:55 by tburtin           #+#    #+#             */
/*   Updated: 2024/04/18 15:08:06 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// ajouter empty
void	modife_infile(t_data *current_data)
{
	if (current_data && ft_compare(current_data->infile[0], "fd[0]") == 1)
	{
		free(current_data->infile[0]);
		current_data->infile[0] = ft_strdup("empty");
	}
}

void	delate_data(t_data **liste_data, t_data	*current_data)
{
	t_data	*temp;

	if (current_data->prev == NULL)
	{
		*liste_data = current_data->next;
		if (*liste_data != NULL)
				(*liste_data)->prev = NULL;
	}
	else
	{
		temp = current_data->prev;
		temp->next = current_data->next;
		if (current_data->next != NULL)
				current_data->next->prev = temp;
	}
	free_onedata(current_data);
}

// supprimer les commande qui on des probleme
void	delete_wrong_data(t_data **liste_data)
{
	t_data	*current_data;

	current_data = *liste_data;
	while (current_data)
	{
		if (current_data->commande_correct == 1
			|| (current_data->commande_correct == 0
				&& ft_compare(current_data->outfile[0], "fd[1]") == 1
				&& current_data
				&& current_data->next->commande_correct == 1))
		{
			delate_data(liste_data, current_data);
			modife_infile(*liste_data);
			current_data = *liste_data;
		}
		else
			current_data = current_data->next;
	}
}

// chek si le fichier exsiste, a les droit ect...
void	algo_chek(t_token *current_token, t_data	*current_data)
{
	if (current_token->type == infile)
	{
		if (chek_infile(current_token->str) == 0)
			current_data->commande_correct = 1;
	}
	else if (current_token->type == outfile)
	{
		if (chek_outfile(current_token->str) == 0)
			current_data->commande_correct = 1;
	}
	else if (current_token->type == append)
	{
		if (chek_append(current_token->str) == 0)
			current_data->commande_correct = 1;
	}
}

//chek chaque data
int	chek_ligne(t_token *liste_token, t_data **liste_data, t_list **liste_envp)
{
	t_data	*cur;

	cur = *liste_data;
	while (cur)
	{
		while (liste_token && liste_token->type != pip)
		{
			algo_chek(liste_token, cur);
			liste_token = liste_token->next;
		}
		if (liste_token != NULL)
			liste_token = liste_token->next;
		if (cur->cmd_arg[0] == NULL || chek_command(cur, *liste_envp) == 0)
			cur->commande_correct = 1;
		cur = cur->next;
	}
	delete_wrong_data(liste_data);
	return (1);
}
