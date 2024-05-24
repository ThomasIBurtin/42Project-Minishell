/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:55:53 by tburtin           #+#    #+#             */
/*   Updated: 2024/04/22 21:16:49 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	chek_here_doc(t_data *new, int *position, char *last_outfile)
{
	t_index	index;

	index.i = 0;
	index.j = 0;
	while (new->heredoc[index.i] != NULL)
	{
		create_here_doc(new->heredoc[index.i]);
		if (g_exitstatus == 130)
		{
			free(last_outfile);
			*position = 0;
			unlink(".heredoc.tmp");
			free_onedata(new);
			return (0);
		}
		while (ft_compare(new->infile[index.j], new->heredoc[index.i]) != 1)
			index.j++;
		free(new->heredoc[index.i]);
		free(new->infile[index.j]);
		new->heredoc[index.i] = ft_strdup(".heredoc.tmp");
		new->infile[index.j] = ft_strdup(".heredoc.tmp");
		index.j++;
		index.i++;
	}
	return (1);
}

//remplir les tab de data dans l'ordre
void	input_all_tab(t_token *token, t_data *new, int flag2)
{
	t_len	len;

	init_compteurs(&len);
	if (flag2 == 1)
		len.infile++;
	while (token && token->type != pip)
	{	
		if (token->type == commande || token->type == argument)
			len.cmd = remplir_data(token->str, new->cmd_arg, len.cmd);
		else if (token->type == append)
		{
			len.app = remplir_data(token->str, new->outfile_append, len.app);
			len.outfile = remplir_data(token->str, new->outfile, len.outfile);
		}
		else if (token->type == outfile)
			len.outfile = remplir_data(token->str, new->outfile, len.outfile);
		else if (token->type == here_doc)
		{
			len.here_doc = remplir_data(token->str, new->heredoc, len.here_doc);
			len.infile = remplir_data(token->str, new->infile, len.infile);
		}
		else if (token->type == infile)
			len.infile = remplir_data(token->str, new->infile, len.infile);
		token = token->next;
	}
}

// chek la position pour voir si on a atteint la fin
int	check_position(t_token *liste_token, int *position, char *last_outfile)
{
	int	flag;

	flag = 0;
	*position += 1;
	while (liste_token != NULL)
	{
		if (liste_token->type == commande)
			flag++;
		liste_token = liste_token->next;
	}
	if (flag < 2)
	{
		free(last_outfile);
		*position = 0;
	}
	return (flag);
}

void	add_back_fronts(t_data **liste_data, t_data *new)
{
	t_data	*current;

	new->next = NULL;
	new->prev = NULL;
	if (*liste_data == NULL)
		*liste_data = new;
	else
	{
		current = *liste_data;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
		new->prev = current;
	}
}

t_data	*ft_newcmd(t_token *liste_token)
{
	static int	position = 0;
	static char	*last_outfile = NULL;
	t_data		*new;
	t_len		len;

	new = (t_data *)malloc(sizeof(t_data));
	new->commande_correct = 0;
	len_all_tab(liste_token, &len, position);
	allocation_tab(len, new);
	if (len.flag1 == 1)
		algo_outfile(liste_token, new);
	if (len.flag2 == 1)
		algo_infile(new, position, last_outfile);
	if (last_outfile != NULL)
	{
		free(last_outfile);
		last_outfile = NULL;
	}
	input_all_tab(liste_token, new, len.flag2);
	if (chek_here_doc(new, &position, last_outfile) == 0)
		return (0);
	last_outfile = find_last_outfile(new->outfile);
	if (check_position(liste_token, &position, last_outfile) < 2)
		last_outfile = NULL;
	return (new);
}
