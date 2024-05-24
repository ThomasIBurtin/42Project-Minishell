/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:47:12 by transfo           #+#    #+#             */
/*   Updated: 2024/04/16 11:43:29 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	allocation_tab(t_len len, t_data *new)
{
	new->cmd_arg = (char **)malloc(sizeof(char *)
			* (len.cmd + 1));
	new->outfile = (char **)malloc(sizeof(char *) * (len.outfile + 1));
	new->outfile_append = (char **)malloc(sizeof(char *)
			* (len.app + 1));
	new->infile = (char **)malloc(sizeof(char *) * (len.infile + 1));
	new->heredoc = (char **)malloc(sizeof(char *) * (len.here_doc + 1));
	new->cmd_arg[len.cmd] = NULL;
	new->outfile[len.outfile] = NULL;
	new->outfile_append[len.app] = NULL;
	new->infile[len.infile] = NULL;
	new->heredoc[len.here_doc] = NULL;
}

void	bonus_len(t_len *len, int position)
{
	if (len->outfile == 0)
	{
		len->outfile++;
		len->flag1 = 1;
	}
	if ((position == 0 && len->infile == 0) || (position != 0))
	{
		len->infile++;
		len->flag2 = 1;
	}
}

void	len_all_tab(t_token *liste_token, t_len *len, int position)
{
	init_compteurs(len);
	while (liste_token && liste_token->type != pip)
	{
		if (liste_token->type == commande || liste_token->type == argument)
			len->cmd++;
		else if (liste_token->type == outfile)
			len->outfile++;
		else if (liste_token->type == append)
		{
			len->app++;
			len->outfile++;
		}
		else if (liste_token->type == infile)
			len->infile++;
		else if (liste_token->type == here_doc)
		{
			len->infile++;
			len->here_doc++;
		}
		liste_token = liste_token->next;
	}
	bonus_len(len, position);
}
