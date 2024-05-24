/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chek.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:24:11 by tburtin           #+#    #+#             */
/*   Updated: 2024/04/29 14:41:00 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// chek si le file exsiste
int	chek_infile(char *infile)
{
	int	fd;

	errno = 0;
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			printf("no such file or directory\n");
		else if (errno == EACCES)
			printf("permission denied\n");
		g_exitstatus = 1;
		return (0);
	}
	else
		close(fd);
	return (1);
}

// chek si le file exsiste
int	chek_outfile(char *outfile)
{
	int	fd;

	if (outfile[0] == '\0')
	{
		printf("no such file or drectory\n");
		return (0);
	}
	fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		g_exitstatus = 1;
		printf("permission denied\n");
		return (0);
	}
	else
		close(fd);
	return (1);
}

int	chek_append(char *append)
{
	int	fd;

	if (append[0] == '\0')
	{
		printf("no such file or drectory\n");
		return (0);
	}
	fd = open(append, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		g_exitstatus = 1;
		printf("permission denied\n");
		return (0);
	}
	else
		close(fd);
	return (1);
}

int	util_exit(int nbr_cmds)
{
	if ((nbr_cmds != 0) && (g_exitstatus == 127))
		return (1);
	if ((nbr_cmds != 0) && (g_exitstatus == 126))
		return (1);
	if ((nbr_cmds != 0) && (g_exitstatus == 1))
		return (1);
	if ((nbr_cmds != 0) && (g_exitstatus == 2))
		return (1);
	if ((nbr_cmds != 0) && (g_exitstatus == 0))
		return (1);
	return (0);
}
