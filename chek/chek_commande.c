/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_commande.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:15:45 by tburtin           #+#    #+#             */
/*   Updated: 2024/04/29 14:41:05 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rr(char *path, t_data *liste_data)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			printf("%s", "Is a directory\n");
			return (0);
		}
	}
	if (ft_strnstr(liste_data->cmd_arg[0], "/", 2) == 0)
		free(path);
	return (1);
}

char	*recup_path(char *part_path, char **path_from_envp, t_data data, int j)
{
	char	*path;

	part_path = ft_strjoin(path_from_envp[j], "/");
	path = ft_strjoin(part_path, data.cmd_arg[0]);
	free(part_path);
	return (path);
}

char	*find_path(t_data data, t_list *envp)
{
	char **(path_from_envp) = NULL;
	char *(part_path) = NULL;
	char *(path) = NULL;
	int (j) = 0;
	if (ft_strnstr(data.cmd_arg[0], "/", 2) != 0
		&& access(data.cmd_arg[0], F_OK) == 0)
		return ((char *)data.cmd_arg[0]);
	if (envp == NULL || envp->content == NULL)
		return (NULL);
	while (envp->next && ft_strnstr(envp->content, "PATH=", 5) == 0)
		envp = envp->next;
	if (ft_strnstr(envp->content, "PATH=", 5) == 0
		|| ft_strnstr(data.cmd_arg[0], "/", 2))
		return (NULL);
	path_from_envp = ft_split(envp->content + 5, ':');
	while (path_from_envp[j])
	{
		path = recup_path(part_path, path_from_envp, data, j);
		j++;
		if (access(path, F_OK) == 0)
			return ((free_tab((char **)path_from_envp)), path);
		free((char *)path);
	}
	free_tab((char **)path_from_envp);
	return (NULL);
}

void	path_null(t_data *liste_data)
{
	if (ft_strnstr(liste_data->cmd_arg[0], "/", 2) != 0
		|| liste_data->cmd_arg[0][ft_strlen(liste_data->cmd_arg[0]) - 1] == 47)
	{
		printf("%s : No such file or directory\n", liste_data->cmd_arg[0]);
		g_exitstatus = 126;
	}
	else
	{
		printf("%s : command not found\n", liste_data->cmd_arg[0]);
		g_exitstatus = 127;
	}
}

int	chek_command(t_data *liste, t_list *liste_envp)
{
	char		*path;

	if (is_built_in(*liste) == 1)
		return (1);
	else
	{
		if (liste->cmd_arg[0][0] == '\0'
			|| (liste->cmd_arg[0][1] && liste->cmd_arg[0][0] == '.'
				&& liste->cmd_arg[0][1] == '.')
			|| (liste->cmd_arg[0][0] == '.' && liste->cmd_arg[0][1] == '\0'))
		{
			printf("command not found\n");
			g_exitstatus = 127;
			return (0);
		}
		path = find_path(*liste, liste_envp);
		if (path == NULL)
		{
			path_null(liste);
			return (0);
		}
		if (rr(path, liste) == 0)
			return (0);
	}
	return (1);
}
