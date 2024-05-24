/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:11:10 by tburtin           #+#    #+#             */
/*   Updated: 2024/04/09 15:29:07 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	algo_outfile(t_token *liste_token, t_data *new)
{
	while (liste_token)
	{
		if (liste_token->type == pip)
		{
			new->outfile[0] = ft_strdup("fd[1]");
			return ;
		}
		liste_token = liste_token->next;
	}
	new->outfile[0] = ft_strdup("/dev/stdout");
}

void	algo_infile(t_data *new, int position, char *last_outfile)
{
	if (position == 0)
		new->infile[0] = ft_strdup("/dev/stdin");
	else
	{
		if (ft_compare(last_outfile, "fd[1]") == 1)
			new->infile[0] = ft_strdup("fd[0]");
		else
			new->infile[0] = ft_strdup("empty");
	}
}

char	*find_last_outfile(char **tab)
{
	int	i;

	i = 0;
	while (tab[i + 1] != NULL)
		i++;
	return (ft_strdup(tab[i]));
}

int	remplir_data(char *str, char **tab, int compteur)
{
	tab[compteur] = ft_strdup(str);
	return (compteur + 1);
}

void	init_compteurs(t_len *len)
{
	len->cmd = 0;
	len->app = 0;
	len->outfile = 0;
	len->here_doc = 0;
	len->infile = 0;
	len->flag1 = 0;
	len->flag2 = 0;
}
