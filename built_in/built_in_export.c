/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:46:12 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/05/14 13:57:24 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_invalid_identifier(char *var)
{
	printf("%s %s \n", var, "not a valid identifier");
	g_exitstatus = 1;
}

/*split la variable VAR=content en un char** */
char	**get_variable(char *var)
{
	char	**tmp;
	char	**dest;

	dest = NULL;
	if (var[0] == '=')
		ft_invalid_identifier(var);
	else if (ft_strnstr(var, "=", ft_strlen(var)))
	{
		tmp = ft_split(var, '=');
		dest = malloc(2 * sizeof(char *));
		if (!dest)
			return (NULL);
		if (ft_strchr(var, '=') == 0)
			fill_dest(var, dest);
		else if (chek_nonvalid_var(tmp[0]) == 1)
			fill_dest(tmp[0], dest);
		free_tab(tmp);
		return (dest);
	}
	return (NULL);
}

/*verifier si la variable existe deja*/
int	check_already_exist_envp(char *variable, t_list *envp)
{
	char	**tab;

	while ((envp != NULL && envp->content != NULL)
		&& (envp->content[0] != '\0'))
	{
		tab = ft_split(envp->content, '=');
		if (ft_compare(tab[0], variable) == 1)
		{
			free_tab(tab);
			return (1);
		}
		free_tab(tab);
		if (envp->next == NULL || envp->next->content[0] == '\0'
			|| envp->next->content == NULL)
			break ;
		envp = envp->next;
	}
	return (0);
}

/*modif une variable qui existe*/
void	edit_envp(char *var, char *cmd, t_list **envp)
{
	t_list	*current_node;
	t_list	*previous_node;
	t_list	*next_node;
	t_list	*new_node;

	new_node = ft_lstnew(cmd);
	current_node = *envp;
	while (ft_strncmp(current_node->content, var, ft_strlen(var)) != 0)
	{
		previous_node = current_node;
		current_node = current_node->next;
		next_node = current_node->next;
	}
	if (current_node == *envp)
	{
		new_node->next = current_node->next;
		*envp = new_node;
	}
	else
	{
		previous_node->next = new_node;
		new_node->next = next_node;
	}
	free(current_node->content);
	free(current_node);
}

void	built_in_export(t_data *data, t_list **envp)
{
	char **(variable) = NULL;
	t_list *(new_node) = NULL;
	int (i) = 1;
	int (nbr_args) = 0;
	nbr_args = number_of_args(data->cmd_arg);
	while (i < nbr_args)
	{	
		if (without_env(data, i) != 0)
		{
			variable = get_variable(data->cmd_arg[i]);
			if (variable != NULL)
			{
				if (check_already_exist_envp(variable[0], *envp) == 1)
					edit_envp(variable[0], data->cmd_arg[i], envp);
				else
				{
					new_node = ft_lstnew(data->cmd_arg[i]);
					ft_lstadd_back(envp, new_node);
				}
				free_tab(variable);
			}
		}
		i++;
	}
	unlink_if_needed(*data);
}
