/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:33:17 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/30 09:39:35 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*existe uniquement a cause des 25 lignes*/
static void	child_process_else(t_data *data, int *fd, pid_t id)
{
	int	infile;
	int	i;

	if (is_built_in(*data) == 1)
		waitpid(id, NULL, 0);
	unlink_if_needed(*data);
	i = get_index_file((*data).next->infile);
	if (!ft_strncmp(data->next->infile[i], "fd[0]", ft_strlen("fd[0]"))
		&& ft_strlen("fd[0]") == ft_strlen(data->next->infile[i]))
	{
		close (fd[1]);
		redirect_and_close(fd[0], STDIN_FILENO);
	}
	else
	{
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
		{
			perror("invalid close ");
			return ;
		}
		infile = get_infile(*data->next);
		redirect_and_close(infile, STDIN_FILENO);
	}
}

/*cas ou on utilise un pipe*/
void	child_process_with_pipe(t_data *data, t_list **envp, int in, int out)
{
	int		fd[2];
	pid_t	id;

	if (pipe(fd) == -1)
	{
		perror("pipe ");
		g_exitstatus = 1;
	}
	id = fork();
	if (id == -1)
	{
		perror("fork ");
		g_exitstatus = 1;
	}
	else if (id == 0)
	{
		if (close(fd[0]) == -1)
			perror("invalid close ");
		redirect_and_close(fd[1], STDOUT_FILENO);
		execute(*data, *envp, in, out);
	}
	else
		child_process_else(data, fd, id);
}

/*cas ou on ecrit dans un outfile intermediaire*/
void	child_process_without_pipe(t_data *data, t_list **envp, int i, int o)
{
	pid_t	id;
	int		outfile;
	int		infile;

	outfile = get_outfile(*data);
	id = fork();
	if (id == -1)
	{
		perror("fork ");
		g_exitstatus = 1;
	}
	else if (id == 0)
	{
		redirect_and_close(outfile, STDOUT_FILENO);
		execute(*data, *envp, i, o);
	}
	else
	{
		close(outfile);
		unlink_if_needed(*data);
		infile = get_infile(*data->next);
		redirect_and_close(infile, STDIN_FILENO);
	}
}

/*existe uniquement a cause des 25 lignes*/
static void	child_final_suite(int outfile, t_data data)
{
	close(outfile);
	unlink_if_needed(data);
}

/*gestion de la derniere/unique commande*/
int	child_process_final(t_data *data, t_list **envp, int in, int out)
{
	pid_t	id;
	int		outfile;

	outfile = get_outfile(*data);
	if (is_built_in(*data) == 1)
	{
		close_when_exit(*data, in, out);
		redirect_and_close(outfile, STDOUT_FILENO);
		return (exec_built_in(*data, envp));
	}
	else
	{
		id = fork();
		if (id == -1)
			put_mess_and_get_exit("fork ", 1, 1);
		else if (id == 0)
		{
			redirect_and_close(outfile, STDOUT_FILENO);
			execute(*data, *envp, in, out);
		}
		else
			child_final_suite(outfile, *data);
	}
	return (0);
}
