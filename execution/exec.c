/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:15:05 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/30 10:32:38 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*check si la cmd est un built_in*/
int	is_built_in(t_data data)
{
	size_t	len_cmd;

	len_cmd = ft_strlen(data.cmd_arg[0]);
	if ((ft_strncmp(data.cmd_arg[0], "cd", 2) == 0) && len_cmd == 2)
		return (1);
	else if ((ft_strncmp(data.cmd_arg[0], "echo", 4) == 0) && len_cmd == 4)
		return (1);
	else if ((ft_strncmp(data.cmd_arg[0], "env", 3) == 0) && len_cmd == 3)
		return (1);
	else if ((ft_strncmp(data.cmd_arg[0], "exit", 4) == 0) && len_cmd == 4)
		return (1);
	else if ((ft_strncmp(data.cmd_arg[0], "export", 6) == 0) && len_cmd == 6)
		return (1);
	else if ((ft_strncmp(data.cmd_arg[0], "pwd", 3) == 0) && len_cmd == 3)
		return (1);
	else if ((ft_strncmp(data.cmd_arg[0], "unset", 5) == 0) && len_cmd == 5)
		return (1);
	return (0);
}

/*execute le built_in*/
int	exec_built_in(t_data data, t_list **envp)
{
	size_t	len_cmd;

	len_cmd = ft_strlen(data.cmd_arg[0]);
	if ((ft_strncmp(data.cmd_arg[0], "cd", 2) == 0) && len_cmd == 2)
		built_in_cd(data, envp);
	else if ((ft_strncmp(data.cmd_arg[0], "echo", 4) == 0) && len_cmd == 4)
		built_in_echo(data);
	else if ((ft_strncmp(data.cmd_arg[0], "env", 3) == 0) && len_cmd == 3)
		built_in_env(data, *envp);
	else if ((ft_strncmp(data.cmd_arg[0], "exit", 4) == 0) && len_cmd == 4)
		return (built_in_exit(data));
	else if ((ft_strncmp(data.cmd_arg[0], "export", 6) == 0) && len_cmd == 6)
		built_in_export(&data, envp);
	else if ((ft_strncmp(data.cmd_arg[0], "pwd", 3) == 0) && len_cmd == 3)
		built_in_pwd(data);
	else if ((ft_strncmp(data.cmd_arg[0], "unset", 5) == 0) && len_cmd == 5)
		built_in_unset(&data, envp);
	return (0);
}

/*execute la cmd (built-in ou non)*/
void	execute(t_data	data, t_list *envp, int in, int out)
{
	const char	*path;
	char		**env;

	close(in);
	close(out);
	if (is_built_in(data) == 1)
		exec_built_in(data, &envp);
	else
	{
		path = find_path(data, envp);
		env = recup_envp(envp);
		if (execve(path, data.cmd_arg, env) == -1)
		{
			g_exitstatus = 1;
			perror("execve ");
		}
	}
}

/*existe seulement a cause de la regle des 25 lignes*/
static void	exec_line_suite(int nbr_cmds, t_data data)
{
	int	status;
	int	*exit_statuses;

	int (i) = 0;
	if (is_built_in(data) != 1)
	{
		exit_statuses = malloc(sizeof(int) * nbr_cmds);
		while (i < nbr_cmds)
		{
			waitpid(-1, &status, 0);
			exit_statuses[i++] = WEXITSTATUS(status);
		}
		i = 0;
		while (i < nbr_cmds)
		{
			if (exit_statuses[i] != 0 || util_exit(nbr_cmds) == 1)
			{
				g_exitstatus = exit_statuses[i];
				break ;
			}
			i++;
		}
		free(exit_statuses);
	}
}

/*Fonction principale d'execution*/
void	execute_line(t_data *data, t_list **envp, int *is_exit)
{
	int	nbr_cmds;
	int	infile;
	int	orig_stdin;
	int	orig_stdout;

	int (i) = 1;
	nbr_cmds = ft_datasize(data);
	set_original_std(&orig_stdin, &orig_stdout);
	infile = get_infile(*data);
	redirect_and_close(infile, STDIN_FILENO);
	while (i < nbr_cmds)
	{
		if (!ft_strncmp(data->outfile[0], "fd[1]", ft_strlen(data->outfile[0]))
			&& (ft_strlen(data->outfile[0]) == ft_strlen("fd[1]")))
			child_process_with_pipe(data, envp, orig_stdin, orig_stdout);
		else
			child_process_without_pipe(data, envp, orig_stdin, orig_stdout);
		i++;
		data = data->next;
	}
	*is_exit = child_process_final(data, envp, orig_stdin, orig_stdout);
	put_orig_std_back(data, orig_stdin, orig_stdout);
	exec_line_suite(nbr_cmds, *data);
}
