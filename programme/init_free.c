/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:40:23 by transfo           #+#    #+#             */
/*   Updated: 2024/04/26 17:59:40 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_programme(t_programme *programme, char **envp)
{
	programme->liste_variable = (t_list **)malloc(sizeof(t_list *));
	programme->envp = (t_list **)malloc(sizeof(t_list *));
	*programme->liste_variable = NULL;
	*programme->envp = NULL;
	remplir_liste(envp, programme->envp, programme);
	deal_with_envi(programme->envp);
}

void	init_data(t_programme *programme)
{
	programme->args = readline("minishell > ");
	if (programme->args && programme->args[0])
		add_history(programme->args);
	programme->split_args = NULL;
	programme->liste_token = (t_token **)malloc(sizeof(t_token *));
	programme->data = (t_data **)malloc(sizeof(t_data *));
	*programme->liste_token = NULL;
	*programme->data = NULL;
}

void	free_data(t_programme *programme)
{
	free(programme->args);
	if (programme->split_args != NULL)
		free_tab((char **)programme->split_args);
	if (*programme->liste_token != NULL)
		free_t_token(*programme->liste_token);
	free(programme->liste_token);
	if (*programme->data != NULL)
		free_t_data(*programme->data);
	free(programme->data);
}

void	free_programme(t_programme *programme)
{
	if (*programme->liste_variable != NULL)
		free_t_liste(*programme->liste_variable);
	free(programme->liste_variable);
	if (programme->envp != NULL)
	{
		free_t_liste(*programme->envp);
		free(programme->envp);
	}
	clear_history();
}
