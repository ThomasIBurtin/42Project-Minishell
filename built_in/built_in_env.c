/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:28:40 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/30 09:28:32 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	deal_with_envi(t_list **envp)
{
	t_list	*new_node;
	char	cwd[PATH_MAX];
	char	*content;
	char	*var_tot;

	if (check_already_exist_envp("PWD", *envp) != 1)
	{
		content = getcwd(cwd, sizeof(cwd));
		var_tot = ft_strjoin("PWD=", content);
		new_node = ft_lstnew(var_tot);
		ft_lstadd_back(envp, new_node);
		free(var_tot);
	}
	if (check_already_exist_envp("_", *envp) != 1)
	{
		content = ft_strdup("/usr/bin/env");
		var_tot = ft_strjoin("_=", content);
		new_node = ft_lstnew(var_tot);
		ft_lstadd_back(envp, new_node);
		free(content);
		free(var_tot);
	}
}

/*affiche l'environnement*/
void	built_in_env(t_data data, t_list *envp)
{
	char	*argv[1];
	char	*env[1];

	argv[0] = NULL;
	env[0] = NULL;
	while (envp)
	{
		printf("%s\n", envp->content);
		envp = envp->next;
	}
	unlink_if_needed(data);
	if (data.next != NULL && data.next->cmd_arg != NULL)
		execve("/bin/true", argv, env);
}
