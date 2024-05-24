/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:32:57 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/30 09:18:43 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*existe seulement a cause des 25 lignes*/
static void	built_in_cd_suite(t_list **envp, char *path, t_data data)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		perror("chdir()");
		g_exitstatus = 1;
	}
	pwd = getcwd(NULL, 0);
	edit_pwd_oldpwd(envp, pwd, oldpwd);
	free(oldpwd);
	free(pwd);
	if (!(data.cmd_arg[1] == NULL || data.cmd_arg[1][0] == '\0'
		|| data.cmd_arg[1][0] == '~'
		|| (data.cmd_arg[1][0] == '-' && data.cmd_arg[1][1] == '-')))
		free(path);
	unlink_if_needed(data);
}

/*existe seulement a cause des 25 lignes*/
static void	cd_not_home(t_data data, char **path, t_list **envp)
{
	if (data.cmd_arg[1][0] == '-')
	{
		*path = get_oldpwd(*envp);
		if (*path != NULL)
			printf("%s\n", *path);
		else
			ft_putstr_fd("OLDPWD environment variable not set\n", 2);
	}
	else
		*path = ft_strdup(data.cmd_arg[1]);
}

/*recupere le bon path et change de directory*/
static void	exec_built_in_cd(t_data data, t_list **envp)
{
	char	*home;
	char	*path;

	if (data.cmd_arg[1] == NULL || data.cmd_arg[1][0] == '\0'
		|| data.cmd_arg[1][0] == '~'
		|| (data.cmd_arg[1][0] == '-' && data.cmd_arg[1][1] == '-'))
	{
		if (data.cmd_arg[1] && data.cmd_arg[1][0] == '-'
			&& data.cmd_arg[1][1] == '-' && data.cmd_arg[1][2] != '\0')
		{
			put_mess_and_get_exit("invalid option\n", 2, 0);
			return ;
		}
		home = getenv("HOME");
		if (home == NULL)
		{
			ft_putstr_fd("HOME environment variable not set\n", 2);
			return ;
		}
		path = home;
	}
	else
		cd_not_home(data, &path, envp);
	if (path != NULL)
		built_in_cd_suite(envp, path, data);
}

void	built_in_cd(t_data data, t_list **envp)
{
	char	cwd[PATH_MAX];
	char	*home;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		home = getenv("HOME");
		if (home == NULL)
			return ;
		chdir(home);
		return ;
	}
	else
		exec_built_in_cd(data, envp);
}
