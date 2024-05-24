/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:32:21 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/30 09:20:01 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*recupere l'ancien directory*/
char	*get_oldpwd(t_list *envp)
{
	char	*oldpwd;

	while (envp->next && ft_strnstr(envp->content, "OLDPWD=", 7) == 0)
		envp = envp->next;
	if (ft_strnstr(envp->content, "OLDPWD=", 7) == 0)
		return (NULL);
	oldpwd = ft_strdup(envp->content + 7);
	return (oldpwd);
}

/*modifie PWD et OLDPWD dans l'env*/
void	edit_pwd_oldpwd(t_list **envp, char *pwd, char *oldpwd)
{
	char	*cmd_pwd;
	char	*cmd_oldpwd;

	cmd_pwd = ft_strjoin("PWD=", pwd);
	cmd_oldpwd = ft_strjoin("OLDPWD=", oldpwd);
	if (check_already_exist_envp("PWD", *envp) == 1)
		edit_envp("PWD", cmd_pwd, envp);
	if (check_already_exist_envp("OLDPWD", *envp) == 1)
		edit_envp("OLDPWD", cmd_oldpwd, envp);
	free(cmd_pwd);
	free(cmd_oldpwd);
}
