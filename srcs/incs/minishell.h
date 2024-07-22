/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:27:38 by glions            #+#    #+#             */
/*   Updated: 2024/07/22 17:32:10 by glions           ###   ########.fr       */
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
	WHITE_SPACE,
	DOUBLE_QUOTE,
	QUOTE,
	HERE_DOC_IN,
	HERE_DOC_OUT,
	REDIR_OUT,
	REDIR_IN,
	PIPE_LINE,
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

typedef struct s_cmd_utils
{
	int					n_pipe;
	int					n_cmd;
}						t_cmd_utils;

typedef struct s_cmd
{
	int					pid;
	int					status;
	int					id;
	char				**tab_opt;
	t_redir				*list_redirc;
	int					**tab_pipes;
	t_cmd_utils			utils;
	struct s_cmd		*next;
	int					pos_cmd;
	int					**tab_fd;
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
	int					status;
	int					flag_env;
}						t_minish;

int						get_heredoc(t_redir *curr, int i);
int						exec_heredoc(t_cmd *curr);
int						check_if_heredoc(t_cmd *cmd);
int						close_tmp_file(t_cmd *cmd);

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
int						new_cmd(char *str, t_minish *dt_minish, int *i,
							t_dt_elem **curr_block);

// TOKENS
int						token_quotes(char *str, t_dt_elem **token,
							t_check *check, char c);
int						tokens_redir(char *str, t_dt_elem **token,
							t_check *check, int *j);
int						token_whitespace(char *str, t_dt_elem **token,
							t_check *check, int j);
int						token_word(char *str, t_dt_elem **token, t_minish *dt_minish,
							int *j);
int						tokens_dollar(char *str, t_dt_elem **token,
							t_minish *dt_minish, int *j);

//// EXEC
int						start_exec(t_minish *dt_minish);
int						exec_cmd(t_cmd *cmd, t_minish *dt);
int						child_process3(t_cmd *cmd, t_minish *dt);
int						child_process2(t_cmd *cmd, t_minish *dt);
int						child_process1(t_cmd *cmd, t_minish *dt);
int						get_redir(t_cmd *curr_cmd, int *n_redir_out,
							int *n_redir_in);
int						count_redirc(t_redir *list);
int						count_pipe(t_cmd *cmd, int *n_pipe);
int						close_tmp_file(t_cmd *cmd);
int						init_tab_fd(t_cmd *curr_cmd);
void					close_tab_pipes(t_cmd *cmd);
int						**init_tab_pipes(int n_pipe, int ***tab);
int						nb_cmd(t_cmd *cmd);
int						exec_simple_cmd(t_cmd *cmd, t_minish *dt);
char					*get_path(t_cmd *cmd, t_minish *dt);
void					close_cmd(t_cmd *cmd);
int						init_cmd(t_dt_elem *tokens, t_cmd **new_c,
							t_minish *dt_minish);
char					**gen_env(t_list_gl *env);

//// UTILS
// CREATE
t_check					*create_check(void);
t_minish				*create_minish(char **envp);
t_dt_elem				*create_dt_elem(char *value, enum e_type type,
							enum e_state state);
t_cmd					*create_cmd(t_dt_elem **start, t_minish *dt_minish);

// DUP
t_node_env				*dup_node_env(t_node_env *dt);

// FREE
void					free_cmd(void *param);
void					free_node_env(void *env);
void					free_check(t_check *dt);
void					free_minish(t_minish *dt);
void					free_dt_elem(t_dt_elem **dt);
int						remove_dt_elem(t_dt_elem **list, t_dt_elem **elem);
void					free_fd(t_cmd *curr_cmd);

// PRINT
void					print_check(t_check *dt);
void					print_env(t_list_gl *env);
void					print_dt_elem(t_dt_elem *elem);
void					print_cmd(t_cmd *cmd, int mode);

// SYNTAX
int	is_redir(char *str);
int						is_white(char c);
int						accept_char(char c);
int						type_is_redir(enum e_type type);
int						type_is_operator(enum e_type type);
int						type_is_quote(enum e_type type);
int						type_accept_for_quote(enum e_type type);

// DOLLAR
char					*ft_getenv(char *name, t_list_gl *env);

int						modif_env(t_cmd *cmd);
int						change_dir(t_cmd *cmd, t_minish *dt, int pos,
							int change);
int						parent_task(t_minish *dt);
void					ft_pwd(void);
int						other_built(t_cmd *curr, t_minish *dt);

#endif