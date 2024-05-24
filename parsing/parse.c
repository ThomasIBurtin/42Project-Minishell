/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:18:00 by transfo           #+#    #+#             */
/*   Updated: 2024/05/14 14:04:59 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(char *str)
{
	char	*temp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	temp = malloc(sizeof(char ) * len_new_tab(str));
	while (str[i])
	{
		if (str[i +1] && ((str[i] == 39 && str[i +1] == 39)
				|| (str[i] == 34 && str[i +1] == 34)))
			i += 2;
		else
		{
			temp[k] = str[i];
			k++;
			i++;
		}
	}
	temp[k] = '\0';
	free(str);
	return (temp);
}

char	**insert_null(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		tab[i] = remove_quotes(tab[i]);
		i++;
	}
	return (tab);
}

int	get_tokens(char **args, t_programme *programme)
{
	t_token	*new;
	int		i;

	i = 0;
	while (args[i])
	{
		new = ft_newtoken(args[i], programme);
		add_back_front(programme->liste_token, new);
		i++;
	}
	if (get_type_arg(programme->liste_token) == 0)
		return (0);
	return (1);
}

int	add_data(t_data **liste_data, t_token *liste_token)
{
	t_data	*new;

	while (liste_token)
	{
		if (liste_token->prev == NULL || liste_token->type == pip)
		{
			if (liste_token->type == pip)
				liste_token = liste_token->next;
			new = ft_newcmd(liste_token);
			if (new == NULL)
				return (0);
			add_back_fronts(liste_data, new);
		}
		liste_token = liste_token->next;
	}
	return (1);
}

int	parse(t_programme *prog)
{
	if (ft_strlen(prog->args) < 1)
		return (0);
	if (check_quotes(prog->args) == 0)
	{
		g_exitstatus = 130;
		printf("Quotes\n");
		return (0);
	}
	prog->args = insert_spaces(prog->args);
	prog->split_args = (char *const *)ft_split(prog->args, ' ');
	prog->split_args = insert_null((char **)prog->split_args);
	if (prog->split_args == NULL)
		return (0);
	if (get_tokens((char **)prog->split_args, prog) == 0)
	{
		g_exitstatus = 2;
		printf("syntax error near unexpected token\n");
		return (0);
	}
	g_exitstatus = 0;
	if (add_data(prog->data, *prog->liste_token) == 0)
		return (0);
	if (gg(*prog->data) == 0)
		return (0);
	return (1);
}
