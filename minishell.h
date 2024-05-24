/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:17:04 by sdeutsch          #+#    #+#             */
/*   Updated: 2024/04/30 10:33:57 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/stat.h>
# include <stdio.h>

extern int	g_exitstatus;

# define LLINT long long int

typedef struct s_index
{
	int	i;
	int	j;
}	t_index;

typedef struct s_len
{
	int	cmd;
	int	outfile;
	int	app;
	int	infile;
	int	here_doc;
	int	flag1;
	int	flag2;
}	t_len;

typedef enum s_type
{
	commande,
	argument,
	outfile,
	append,
	infile,
	pip,
	here_doc,
	none,
}	t_type;

typedef struct s_token
{
	char			*str;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char			**cmd_arg;
	char			**outfile;
	char			**outfile_append;
	char			**infile;
	char			**heredoc;
	int				commande_correct;
	int				orig_stdin;
	int				orig_stdout;
	struct s_data	*prev;
	struct s_data	*next;
}	t_data;

typedef struct s_programme
{
	char		*args;
	char *const	*split_args;
	t_token		**liste_token;
	t_data		**data;
	t_list		**liste_variable;
	t_list		**envp;
}	t_programme;

/*EXECUTION*/
/*check_and_get_files.c*/
int		check_if_empty(char *infile);
int		check_if_heredoc(char *infile, t_data data);
int		get_infile(t_data data);
int		get_outfile(t_data	data);
/*child_process*/
void	child_process_with_pipe(t_data *data, t_list **envp, int in, int out);
void	child_process_without_pipe(t_data *data, t_list **envp, int i, int o);
int		child_process_final(t_data *data, t_list **envp, int in, int out);
/*exec.c*/
int		is_built_in(t_data data);
int		exec_built_in(t_data data, t_list **envp);
void	execute(t_data	data, t_list *envp, int in, int out);
void	execute_line(t_data *data, t_list **envp, int *is_exit);
/*heredoc.c*/
void	create_here_doc(char *delimiter);
/*util_exec.c*/
void	redirect_and_close(int fd1, int fd2);
char	*find_path(t_data data, t_list *envp);
int		get_index_file(char	**file);
void	unlink_if_needed(t_data data);
int		ft_datasize(t_data *data);
char	**recup_envp(t_list *envp);
/*signal.c*/
void	sig_handler(int sig);
void	sig_handler_in_child(int sig);
void	sig_handler_in_heredoc(int sig);
void	ft_signal(void);
void	close_when_exit(t_data data, int in, int out);

/*BUILT_IN*/
int		without_env(t_data *data, int i);
void	built_in_cd(t_data data, t_list **envp);
int		number_of_args(char **cmd_arg);
void	built_in_echo(t_data data);
void	built_in_env(t_data data, t_list *envp);
int		infinite_modulo(int num);
int		built_in_exit(t_data data);
LLINT	ft_atoll(const char *str);
int		check_ll(char *number);
void	ft_invalid_identifier(char *var);
void	fill_dest(char *content, char **dest);
void	built_in_export(t_data *data, t_list **envp);
void	built_in_pwd(t_data data);
void	built_in_unset(t_data *data, t_list **envp);
char	**get_variable(char *var);
int		check_already_exist_envp(char *variable, t_list *envp);
void	edit_envp(char *var, char *cmd, t_list **envp);
void	set_original_std(int *orig_stdin, int *orig_stdout);
void	apply_orig_std(int stdin, int stdout, t_data *data);
void	restore_original_std(int orig_std, int std_std);
void	put_orig_std_back(t_data *data, int orig_stdin, int orig_stdout);
void	put_mess_and_get_exit(char *err_msg, int err_nb, int is_perror);
void	deal_with_envi(t_list **envp);

//init_free
void	init_programme(t_programme *programme, char **envp);
void	free_programme(t_programme *programme);
void	init_data(t_programme *programme);
void	free_data(t_programme *programme);
void	free_t_token(t_token *token);
void	free_t_data(t_data *data);
void	free_t_liste(t_list *var);
void	free_onedata(t_data *data);
int		gg(t_data *liste_data);
//parsing
int		parse(t_programme *programme);
int		check_quotes(char *str);
char	*insert_spaces(char *str);
int		len_new_tab(char *str);
//token
t_token	*ft_newtoken(char *str, t_programme *programme);
void	add_back_front(t_token **liste_token, t_token *new);
t_type	get_type_arg(t_token **liste_token);
char	*extracte_cle(char *str, int *i);
int		len_commande(char *str, t_programme *programme);
char	**find_value(t_list *list, char *cle);
void	norminette(t_token *new, t_index *index, char *str);
int		util_exit(int nbr_cmds);
//data
t_data	*ft_newcmd(t_token *liste_token);
void	add_back_fronts(t_data **liste_data, t_data *new);
//data_len
void	len_all_tab(t_token *liste_token, t_len *len, int position);
void	bonus_len(t_len *len, int position);
void	allocation_tab(t_len len, t_data *new);
//utils_data
void	algo_outfile(t_token *liste_token, t_data *new);
void	algo_infile(t_data *new, int position, char *last_outfile);
char	*find_last_outfile(char **tab);
int		remplir_data(char *str, char **tab, int compteur);
void	init_compteurs(t_len *len);
//variable
int		variable(t_programme *programme);
void	remplir_liste(char **tab, t_list **list, t_programme *programme);
int		check_already_exist(char *variable_split, t_list *list);
void	replace_var(int index, char *var, t_list **list);
int		recup_exit(t_data data);
int		chek_nonvalid_var(char *str);
//chek_ligne
int		chek_ligne(t_token *liste_token, t_data **liste_data,
			t_list **liste_envp);
int		chek_infile(char *infile);
int		chek_outfile(char *outfile);
int		chek_append(char *append);
int		chek_command(t_data *liste_data, t_list *liste_envp);
char	*get_oldpwd(t_list *envp);
void	edit_pwd_oldpwd(t_list **envp, char *pwd, char *oldpwd);

#endif
