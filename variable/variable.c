/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:47:37 by transfo           #+#    #+#             */
/*   Updated: 2024/04/29 10:31:28 by tburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// chek si il y a que des variables
int	check_ifonly_var(char **cmd_arg)
{
	int	i;

	i = 0;
	while (cmd_arg[i])
	{
		if (ft_strchr(cmd_arg[i], '=') == 0)
			return (i);
		i++;
	}
	return (-1);
}

// remplir la liste de variable
void	remplir_liste(char **tab, t_list **list, t_programme *programme)
{
	int (i) = 0;
	t_list *(new) = NULL;
	char **(variable_split) = NULL;
	int (index) = 0;
	int (index2) = 0;
	while (tab[i] != NULL)
	{
		variable_split = ft_split(tab[i], '=');
		if (chek_nonvalid_var(variable_split[0]) == 1)
		{
			index2 = check_already_exist(variable_split[0], *programme->envp);
			index = check_already_exist(variable_split[0], *list);
			if (index2 != -1)
				replace_var(index2, tab[i], programme->envp);
			else if (index != -1)
				replace_var(index, tab[i], list);
			else
			{
				new = ft_lstnew(tab[i]);
				ft_lstadd_back(list, new);
			}
		}
		free_tab(variable_split);
		i++;
	}
}

// remplace la commande si il ny a pas que des variable
char	**replace_commande(char **cmd_arg, int index)
{
	int		save;
	int		compteur;
	int		i;
	char	**result;

	save = index;
	compteur = 0;
	i = 0;
	while (cmd_arg[save])
	{
		compteur++;
		save++;
	}
	result = (char **)malloc(sizeof(char *) * compteur + 1);
	while (cmd_arg[index])
	{
		result[i] = ft_strdup(cmd_arg[index]);
		i++;
		index++;
	}
	result[i] = NULL;
	free_tab(cmd_arg);
	return (result);
}

int	chek_pip(t_data	*liste_data)
{
	int	result;

	result = 0;
	while (liste_data)
	{
		if (ft_strchr(liste_data->cmd_arg[0], '=') == 1
			|| ft_compare(liste_data->cmd_arg[0], "export") == 1
			|| ft_compare(liste_data->cmd_arg[0], "cd") == 1
			|| ft_compare(liste_data->cmd_arg[0], "exit") == 1
			|| ft_compare(liste_data->cmd_arg[0], "unset") == 1)
		{
			if (liste_data->cmd_arg[1] == NULL)
				g_exitstatus = 0;
			else if (ft_compare(liste_data->cmd_arg[0], "exit") == 1)
				g_exitstatus = recup_exit(*liste_data);
			if (liste_data->prev != NULL || liste_data->next != NULL)
			{
				liste_data->commande_correct = 1;
				result = 1;
			}
		}
		liste_data = liste_data->next;
	}
	return (result);
}

// ajouter les variable (ex : toto = salut)
int	variable(t_programme *programme)
{
	int		index;
	t_data	*liste_data;

	liste_data = *programme->data;
	if (liste_data == NULL || liste_data->cmd_arg[0] == NULL
		|| liste_data->cmd_arg[0][0] == '\0'
		|| chek_pip(liste_data) == 1
		|| ft_strchr(liste_data->cmd_arg[0], '=') == 0)
		return (1);
	index = check_ifonly_var(liste_data->cmd_arg);
	if (index == -1)
		remplir_liste(liste_data->cmd_arg, programme->liste_variable,
			programme);
	else
	{
		liste_data->cmd_arg = replace_commande(liste_data->cmd_arg, index);
		return (1);
	}
	g_exitstatus = 0;
	return (0);
}
