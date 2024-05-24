/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:36:02 by transfo           #+#    #+#             */
/*   Updated: 2024/04/30 12:01:12 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// chek si une variable exsite deja
int	check_already_exist(char *variable_split, t_list *list)
{
	char	**var;
	int		i;

	i = 0;
	while (list)
	{
		var = ft_split(list->content, '=');
		if (ft_compare(var[0], variable_split) == 1)
		{
			free_tab(var);
			return (i);
		}
		free_tab(var);
		list = list->next;
		i++;
	}
	return (-1);
}

// remplacer la variable si elle exsite deja
void	replace_var(int index, char *var, t_list **list)
{
	t_list	*current_node;
	t_list	*new_node;
	t_list	*previous_node;

	current_node = *list;
	new_node = ft_lstnew(var);
	previous_node = NULL;
	while (index > 0)
	{
		previous_node = current_node;
		current_node = current_node->next;
		index--;
	}
	if (previous_node == NULL)
	{
		new_node->next = current_node->next;
		*list = new_node;
	}
	else
	{
		previous_node->next = new_node;
		new_node->next = current_node->next;
	}
	free(current_node->content);
	free(current_node);
}

int	recup_exit(t_data data)
{
	int	num;

	if ((ft_atoi(data.cmd_arg[1]) >= 256))
		num = ft_atoi(data.cmd_arg[1]) % 256;
	else if ((ft_atoi(data.cmd_arg[1]) < 0))
	{
		num = ft_atoi(data.cmd_arg[1]);
		num = infinite_modulo(num);
	}
	else
		num = ft_atoi(data.cmd_arg[1]);
	return (num);
}

int	chek_nonvalid_var(char *str)
{
	int (i) = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '_' && str[1] == '\0')
		return (0);
	if (!((str[0] >= 'a' && str[0] <= 'z')
			|| (str[0] >= 'A' && str[0] <= 'Z')
			|| str[0] == '_'))
	{
		ft_invalid_identifier(str);
		return (0);
	}
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] == '_')
				|| (str[i] >= '0' && str[i] <= '9')))
		{
			ft_invalid_identifier(str);
			return (0);
		}
		i++;
	}
	return (1);
}
