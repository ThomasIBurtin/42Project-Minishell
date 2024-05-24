/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: transfo <transfo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:57:39 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/26 14:18:39 by transfo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exitstatus = 130;
	(void)sig;
}

void	sig_handler_in_child(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_exitstatus = 130;
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit", 4);
		write(1, "\n", 1);
		g_exitstatus = 131;
	}
}

void	sig_handler_in_heredoc(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
	else
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		g_exitstatus = 130;
		(void)sig;
	}
}

void	ft_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
}

void	close_when_exit(t_data data, int in, int out)
{
	if ((ft_strncmp(data.cmd_arg[0], "exit", 4) == 0)
		&& (ft_strlen(data.cmd_arg[0]) == 4))
	{
		close(in);
		close(out);
	}
}
