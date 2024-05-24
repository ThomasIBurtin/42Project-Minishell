/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:51:01 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/26 16:53:55 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*existe seulement a cause des 25 lignes*/
void	redirect_and_close(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2 ");
		return ;
	}
	if (close(fd1) == -1)
	{
		perror("invalid close ");
		return ;
	}
}

/*recupere l'index du dernier infile/outfile*/
int	get_index_file(char	**file)
{
	int	i;

	i = 0;
	if (file[0] == NULL)
		return (-1);
	while (file[i])
		i++;
	i--;
	return (i);
}

/*supprime le heredoc ou le fichier empty*/
void	unlink_if_needed(t_data data)
{
	int	i;

	i = 0;
	while (data.infile[i])
	{
		if (check_if_heredoc(data.infile[i], data) == 1)
			unlink(".heredoc.tmp");
		else if (check_if_empty(data.infile[i]) == 1)
			unlink(".empty.tmp");
		i++;
	}
}

/*compte le nombre de commandes de la ligne de code*/
int	ft_datasize(t_data *data)
{
	int		i;
	t_data	*tmp;

	i = 0;
	tmp = data;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

/*copie la t_list envp dans un char ** pour execve*/
char	**recup_envp(t_list *envp)
{
	int		i;
	char	**env;

	i = 0;
	env = malloc((ft_lstsize(envp) + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	while (envp)
	{
		env[i++] = ft_strdup(envp->content);
		envp = envp->next;
	}
	env[i] = NULL;
	return (env);
}
