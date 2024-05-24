/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:31:33 by transfo           #+#    #+#             */
/*   Updated: 2024/04/30 10:34:28 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exitstatus = 0;

static void	main_suite(t_programme programme, int *is_exit)
{
	chek_ligne(*programme.liste_token, programme.data, programme.envp);
	if (*programme.data != NULL)
	{
		signal(SIGINT, sig_handler_in_child);
		signal(SIGQUIT, sig_handler_in_child);
		execute_line(*(programme.data), programme.envp, is_exit);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_programme	programme;
	int			is_exit;

	(void)argc;
	(void)argv;
	is_exit = 0;
	init_programme(&programme, envp);
	while (1)
	{
		ft_signal();
		init_data(&programme);
		if (programme.args == NULL)
		{
			printf("Exit\n");
			free_data(&programme);
			break ;
		}
		if (parse(&programme) == 1 && variable(&programme) == 1)
			main_suite(programme, &is_exit);
		free_data(&programme);
		if (is_exit == 1)
			break ;
	}
	free_programme(&programme);
	exit (g_exitstatus);
}
