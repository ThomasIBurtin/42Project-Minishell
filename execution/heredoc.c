/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:41:45 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/26 16:52:07 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*existe uniquement a cause des 25 lignes*/
static void	check_heredoc(int file)
{
	if (file == -1)
	{
		perror("open heredoc ");
		g_exitstatus = 1;
		exit(EXIT_FAILURE);
	}
}

static void	dup_and_close(int tmp_stdin, int tmp_fd, char *line)
{
	free(line);
	redirect_and_close(tmp_stdin, STDIN_FILENO);
	if (close(tmp_fd) == -1)
	{
		perror("invalid close ");
		return ;
	}
}

static void	suite_heredoc(int *tmp_fd, int *tmp_stdin, char **line)
{
	*line = NULL;
	*tmp_fd = open(".heredoc.tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	check_heredoc(*tmp_fd);
	signal(SIGQUIT, sig_handler_in_heredoc);
	signal(SIGINT, sig_handler_in_heredoc);
	*tmp_stdin = dup(STDIN_FILENO);
}

/*cree un fichier temporaire heredoc ou on ecrit ce qu'on met dans le terminal*/
void	create_here_doc(char *delimiter)
{
	char	*line;
	int		tmp_fd;
	int		tmp_stdin;

	suite_heredoc(&tmp_fd, &tmp_stdin, &line);
	while (1)
	{
		ft_putstr_fd("heredoc >", 1);
		line = get_next_line(STDIN_FILENO);
		if (g_exitstatus == 130)
			break ;
		else if (line == NULL)
		{
			write(1, "\n", 1);
			close(STDIN_FILENO);
			break ;
		}
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter))
			&& ft_strlen(line) == (ft_strlen(delimiter) + 1))
			break ;
		else
			ft_putstr_fd(line, tmp_fd);
		free(line);
	}
	dup_and_close(tmp_stdin, tmp_fd, line);
}
