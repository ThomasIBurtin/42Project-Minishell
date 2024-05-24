/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_get_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:32:48 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/29 16:36:45 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*verifie si le infile de la commande est empty*/
int	check_if_empty(char *infile)
{
	size_t	len_infile;

	len_infile = ft_strlen(infile);
	if ((len_infile == ft_strlen("empty"))
		&& !ft_strncmp(infile, "empty", len_infile))
		return (1);
	return (0);
}

/*verifie si le infile de la commande est un heredoc*/
int	check_if_heredoc(char *infile, t_data data)
{
	int	j;
	int	len_infile;
	int	len_heredoc;

	j = 0;
	len_infile = ft_strlen(infile);
	while (data.heredoc[j])
	{
		len_heredoc = ft_strlen(data.heredoc[j]);
		if ((len_infile == len_heredoc)
			&& (!ft_strncmp(infile, data.heredoc[j], len_infile)))
			return (1);
		j++;
	}
	return (0);
}

/*recupere le fd (int) de l'infile, cree le heredoc si besoin*/
int	get_infile(t_data data)
{
	int	infile;
	int	i;

	i = 0;
	infile = -1;
	while (data.infile[i])
	{
		if (check_if_empty(data.infile[i]) == 1)
			infile = open(".empty.tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
		else
			infile = open(data.infile[i], O_RDONLY);
		if (infile == -1)
			perror("open ici ");
		i++;
		if (data.infile[i] != NULL && infile != -1)
			close(infile);
	}
	return (infile);
}

/*verifie si le outfile de la cmd est append*/
static int	check_if_append(char *outfile, t_data data)
{
	int	j;
	int	len_outfile;
	int	len_outfile_append;

	j = 0;
	len_outfile = ft_strlen(outfile);
	while (data.outfile_append[j])
	{
		len_outfile_append = ft_strlen(data.outfile_append[j]);
		if ((len_outfile == len_outfile_append)
			&& (!ft_strncmp(outfile, data.outfile_append[j], len_outfile)))
			return (1);
		j++;
	}
	return (0);
}

/*recupere le fd (int) de l'outfile, append/trunc si besoin*/
int	get_outfile(t_data	data)
{
	int	outfile;
	int	i;

	i = 0;
	outfile = -1;
	while (data.outfile[i])
	{
		if (check_if_append(data.outfile[i], data) == 1)
			outfile = open(data.outfile[i], O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			outfile = open(data.outfile[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (outfile == -1)
			perror("open ");
		i++;
		if (data.outfile[i] != NULL && outfile != -1)
			close(outfile);
	}
	return (outfile);
}
