/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:38:07 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/29 10:51:02 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_original_std(int *orig_stdin, int *orig_stdout)
{
	*orig_stdin = dup(STDIN_FILENO);
	if (*orig_stdin == -1)
	{
		perror("dup");
		return ;
	}
	*orig_stdout = dup(STDOUT_FILENO);
	if (*orig_stdout == -1)
	{
		perror("dup");
		return ;
	}
}

void	apply_orig_std(int stdin, int stdout, t_data *data)
{
	data->orig_stdin = stdin;
	data->orig_stdout = stdout;
}

void	restore_original_std(int orig_std, int std_std)
{
	if (dup2(orig_std, std_std) == -1)
	{
		perror("dup2 ");
		return ;
	}
	close(orig_std);
}

void	put_orig_std_back(t_data *data, int orig_stdin, int orig_stdout)
{
	int	i;

	apply_orig_std(orig_stdin, orig_stdout, data);
	i = get_index_file(data->outfile);
	if (is_built_in(*data) == 1
		&& ft_strncmp(data->outfile[i], "/dev/stdout", 11))
		restore_original_std((data->orig_stdout), STDOUT_FILENO);
	else
		close(orig_stdout);
	i = get_index_file(data->infile);
	if (ft_strncmp(data->infile[i], "/dev/stdin", 10))
		restore_original_std((data->orig_stdin), STDIN_FILENO);
	else
		close(orig_stdin);
}

void	put_mess_and_get_exit(char *err_msg, int err_nb, int is_perror)
{
	if (is_perror == 1)
		perror(err_msg);
	else
		ft_putstr_fd(err_msg, 2);
	g_exitstatus = err_nb;
}
