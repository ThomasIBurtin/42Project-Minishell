/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:16:40 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/29 13:21:43 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	foncqq(t_list *previous_node, t_list *current_node)
{
	t_list	*temp;

	temp = current_node;
	if (previous_node == NULL)
	{
		temp = current_node->next;
		free(current_node->content);
		current_node->content = ft_strdup(current_node->next->content);
		current_node->next = current_node->next->next;
	}
	else if (current_node->next == NULL)
	{
		current_node = previous_node;
		current_node->next = NULL;
	}
	else
	{
		current_node = current_node->next;
		previous_node->next = current_node;
	}
	free(temp->content);
	free(temp);
}

static void	delete_var(char *var, t_list **envp)
{
	t_list	*current_node;
	t_list	*previous_node;
	char	**key;

	previous_node = NULL;
	current_node = *envp;
	while (current_node)
	{
		key = ft_split(current_node->content, '=');
		if (ft_compare(key[0], var) == 1)
		{
			free_tab(key);
			break ;
		}
		free_tab(key);
		previous_node = current_node;
		current_node = current_node->next;
	}
	if (current_node == NULL
		|| (previous_node == NULL && current_node->next == NULL))
		return ;
	foncqq(previous_node, current_node);
}

/*recupere la variable et si elle existe, la supprime*/
void	built_in_unset(t_data *data, t_list **envp)
{
	int		i;

	i = 1;
	while (data->cmd_arg[i] != NULL)
	{
		if (ft_strncmp(data->cmd_arg[i], "_", 1) == 0
			|| ft_strncmp(data->cmd_arg[i], "PWD", 3) == 0
			|| ft_strncmp(data->cmd_arg[i], "VALGRIND_LIB", 12) == 0
			|| ft_strncmp(data->cmd_arg[i], "LD_PRELOAD", 10) == 0)
			break ;
		delete_var(data->cmd_arg[i], envp);
		unlink_if_needed(*data);
		i++;
	}
}
