/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:26:42 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/29 14:52:30 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*affiche le PWD*/
void	built_in_pwd(t_data data)
{
	char	cwd[PATH_MAX];
	char	*argv[1];
	char	*env[1];

	argv[0] = NULL;
	env[0] = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{	
		perror("getcwd()");
		g_exitstatus = 1;
		unlink_if_needed(data);
		if (data.next != NULL && data.next->cmd_arg != NULL)
			execve("/bin/true", argv, env);
	}
	unlink_if_needed(data);
	if (data.next != NULL && data.next->cmd_arg != NULL)
		execve("/bin/true", argv, env);
}
