/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:27:38 by glions            #+#    #+#             */
/*   Updated: 2024/07/16 16:06:23 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include "builtin.h"

typedef struct s_node_env
{
	char				*name;
	char				*value;
}						t_node_env;

enum					e_state
{
	GENERAL,
	IN_DQUOTE,
	IN_QUOTE
};

enum					e_type
{
	ENV,
	WORD,
	CALCUL,
	WHITE_SPACE,
	DOUBLE_QUOTE,
	QUOTE,
	HERE_DOC_IN,
	HERE_DOC_OUT,
	REDIR_OUT,
	REDIR_IN,
	PIPE_LINE,
	AND,
	OR,
	PARENTH,
	BLOCK,
	CMD
};

typedef struct s_check
{
	char				**bltn;
	char				**oprt;
	char				**redirct;
	char				**paths;
	int					nb_single;
	int					nb_double;
	char				*line_cmd;
	enum e_state		curr_state;
	int					new_command;
	int					wait_file;
	int					dup2;
}						t_check;

typedef struct s_redir
{
	enum e_type			type;
	char				*name_file;
	struct s_redir		*next;
	char				*name_heredoc;
	int					fd_heredoc;
}						t_redir;


typedef struct	s_cmd_utils
{
	int					n_pipe;
	int					n_cmd;
	int					close_in;
}	t_cmd_utils;

typedef struct s_cmd
{
	int					pid;
	int					status;
	int					id;
	char				**tab_opt;
	t_redir				*list_redirc;
	int					**tab_pipes;
	int					*pipe_out;
	int					*pipe_in;
	t_cmd_utils			utils;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_dt_elem
{
	char				*value;
	enum e_state		state;
	enum e_type			type;
	struct s_dt_elem	*content;
	struct s_dt_elem	*next;
}						t_dt_elem;

typedef struct s_minish
{
	t_list_gl			*env_minish;
	t_dt_elem			*block_token;
	t_check				*check;
}						t_minish;

typedef struct s_process_utils
{
	int redir;
	int last;
	int new_p;
	int	close_in;
}	t_process_utils;

typedef struct	s_process
{
	pid_t				pid;
	int					status;
	int					*pipe_in;
	int					*pipe_out;
	t_list_gl			*env;
	char 				**bltn;
	t_list_gl			*childs;
	t_list_gl			*cmds;
	t_process_utils		utils;
	struct s_process 	*parent;
}		t_process;

typedef struct s_block_child
{
	pid_t				pid;
	int					status;
	t_list_gl			*env;
	char				**bltn;
	int					pipe_in;
	int					*pipe_out;
	int					redir;
	int					last;
	t_list_gl			*child;
	t_list_gl			*cmds;
	int					main;
	int					new_p;
	struct s_block_child		*parent;
}						t_block_child;


int	get_heredoc(t_redir *curr, int i);
int	exec_heredoc(t_cmd *curr);
int	check_if_heredoc(t_cmd *cmd);
int	close_tmp_file(t_cmd *cmd);


//// PARSING
int						parsing(t_minish *dt);
int						parsing_syntax(t_check *check);
int						parsing_quote(t_dt_elem **tokens);
int						parsing_last_verif(t_dt_elem **tokens);

int						blockenisation(t_dt_elem **curr_block, char *str,
							t_minish *dt);

int						add_back_elem(t_dt_elem **list, t_dt_elem *new);
void					reset_syntax(t_check *check);

// parsing_operator
int						is_operator(char *str);
int						check_operator(char *str, t_check *check,
							t_dt_elem **curr_block);

// parsing_element
int						new_cmd(char *str, t_check *check, int *i,
							t_dt_elem **curr_block);
int						new_block(t_dt_elem **curr_block, char *str, int *i,
							t_minish *dt);

// TOKENS
int						token_quotes(char *str, t_dt_elem **token,
							t_check *check, char c);
int						tokens_dollar(char *str, t_dt_elem **token,
							t_check *check, int *j);
int						tokens_redir(char *str, t_dt_elem **token,
							t_check *check, int *j);
int						token_whitespace(char *str, t_dt_elem **token,
							t_check *check, int j);
int						token_word(char *str, t_dt_elem **token, t_check *check,
							int *j);

//// EXEC
int						start_exec(t_minish *dt_minish);
void					wait_all_pid(t_process *curr_p);
int						exec_cmd(t_cmd *cmd, t_process *curr_p, t_minish *dt);
int						child_process3(t_cmd *cmd, t_process *curr_p, t_minish *dt);
int						child_process2(t_cmd *cmd, t_process *curr_p, t_minish *dt);
int						child_process1(t_cmd *cmd, t_process *curr_p, t_minish *dt);
int						get_redir(t_cmd *curr_cmd, int *n_redir_out,
							int *n_redir_in);
int						count_redirc(t_redir *list);
int						count_pipe(t_cmd *cmd, int *n_pipe);
int						close_tmp_file(t_cmd *cmd);
int						**init_tab_fd(t_cmd *curr_cmd, int ***fd);
void					close_tab_pipes(int **tab_pipes, int n_pipe);
int						**init_tab_pipes(int n_pipe, int ***tab);
int						nb_cmd(t_cmd *cmd);
int						exec_simple_cmd(t_cmd *cmd, t_process *curr_p, t_minish *dt);
char					*get_path(t_cmd *cmd, t_minish *dt);
void					close_process(t_process *curr_p, t_minish *minish, int mode, int pipe_out);
void					close_cmd(t_cmd *cmd);
int						init_cmd(t_dt_elem **tokens, t_process *curr_p, t_minish *minish, t_cmd **new_c);
int						start_process(t_dt_elem *tokens, t_process *curr_p, t_minish *minish,
						int mode);
int						init_process(t_dt_elem *tokens, t_process *curr_p, t_minish *minish,
						t_process **new_p);

//// UTILS
// CREATE
t_check					*create_check(void);
t_minish				*create_minish(char **envp);
t_dt_elem				*create_dt_elem(char *value, enum e_type type,
							enum e_state state);
t_cmd					*create_cmd(t_dt_elem **start);
t_process				*create_process(char **bltn, t_list_gl *env, t_process *parent);

// DUP
t_node_env				*dup_node_env(t_node_env *dt);

// UPDATE
int						update_block_child_pipe(t_block_child *curr, int after);

// FREE
void					free_cmd(void *param);
void					free_node_env(void *env);
void					free_check(t_check *dt);
void					free_minish(t_minish *dt);
void					free_dt_elem(t_dt_elem **dt);
int						remove_dt_elem(t_dt_elem **list, t_dt_elem **elem);
void					free_fd(int **tab, t_cmd *curr_cmd);
void					free_process(t_process **dt, int mode);


// PRINT
void					print_check(t_check *dt);
void					print_env(t_list_gl *env);
void					print_dt_elem(t_dt_elem *elem);
void					print_cmd(t_cmd *cmd);
void					print_process(t_process *dt, int mode);

// SYNTAX
int						is_white(char c);
int						accept_char(char c);
int						type_is_redir(enum e_type type);
int						type_is_operator(enum e_type type);
int						type_is_quote(enum e_type type);
int						type_accept_for_quote(enum e_type type);

// DOLLAR
int						var_dollar(char *str, int *i, char **res_env);
int						calc_dollar(int *i, char *str, t_check *check,
							char **res_calc);


#endif