NAME        =   minihell

CC          =   cc

CFLAGS      =   -Wall -Werror -Wextra -MMD -g3

INC_LIBFT   =   ./libft/includes
INC_SRCS    =   ./srcs/incs
INC         =   -I$(INC_LIBFT) -I$(INC_SRCS)

#================SRC================

SRC_DIR     = srcs/
BUILT_DIR   = $(SRC_DIR)builtins/
UTILS_DIR   = $(SRC_DIR)utils/
EXEC_DIR   = $(SRC_DIR)exec/
UTILS_FREE_DIR = $(UTILS_DIR)free/
UTILS_PRINT_DIR = $(UTILS_DIR)print/
UTILS_DOLLAR_DIR = $(UTILS_DIR)dollar/
UTILS_DUP_DIR = $(UTILS_DIR)dup/
UTILS_CREATE_DIR = $(UTILS_DIR)create/
UTILS_SYNTAX_DIR = $(UTILS_DIR)syntax/
ECHO_DIR    = $(BUILT_DIR)ft_echo/
PARSING_DIR = $(SRC_DIR)parsing/
PARSING_TOKEN_DIR = $(PARSING_DIR)tokens/

SRC         = main.c

BUILT_SRC   = ft_cd.c ft_env.c ft_export.c ft_pwd.c ft_unset.c

EXEC_SRC	= 	start_exec.c init_cmd.c clean_all.c cmd_utils.c exec_all_cmd.c exec_cmd.c exec_one_cmd.c exec_utils.c heredoc_utils.c gen_env.c

UTILS_FREE_SRC   = free_node_env.c free_minish.c free_check.c free_dt_elem.c free_cmd.c

UTILS_PRINT_SRC	= print_check.c print_env.c print_dt_elem.c print_cmd.c

UTILS_DOLLAR_SRC = ft_dollar.c

UTILS_DUP_SRC = dup_node_env.c

UTILS_CREATE_SRC = create_check.c create_minish.c create_dt_elem.c create_cmd.c

UTILS_SYNTAX_SRC = syntax.c type.c

ECHO_SRC    = ft_echo.c

PARSING_SRC	= parsing.c parsing_syntax.c parsing_operator.c parsing_element.c parsing_quote.c parsing_last_verif.c

PARSING_TOKEN_SRC	= tokens_quote.c tokens_redir.c tokens_other.c

#================OBJ================

OBJ_DIR     = objs/

OBJ         = $(SRC:.c=.o)
OBJ_DIR_SRC = $(addprefix $(OBJ_DIR), $(OBJ))

OBJ_BUILD   = $(BUILT_SRC:.c=.o)
OBJ_DIR_BUILD = $(addprefix $(OBJ_DIR), $(OBJ_BUILD))

OBJ_EXEC   = $(EXEC_SRC:.c=.o)
OBJ_DIR_EXEC = $(addprefix $(OBJ_DIR), $(OBJ_EXEC))

OBJ_UTILS_FREE   = $(UTILS_FREE_SRC:.c=.o)
OBJ_DIR_UTILS_FREE = $(addprefix $(OBJ_DIR), $(OBJ_UTILS_FREE))

OBJ_UTILS_DUP   = $(UTILS_DUP_SRC:.c=.o)
OBJ_DIR_UTILS_DUP = $(addprefix $(OBJ_DIR), $(OBJ_UTILS_DUP))

OBJ_UTILS_PRINT   = $(UTILS_PRINT_SRC:.c=.o)
OBJ_DIR_UTILS_PRINT = $(addprefix $(OBJ_DIR), $(OBJ_UTILS_PRINT))

OBJ_UTILS_CREATE   = $(UTILS_CREATE_SRC:.c=.o)
OBJ_DIR_UTILS_CREATE = $(addprefix $(OBJ_DIR), $(OBJ_UTILS_CREATE))

OBJ_UTILS_DOLLAR   = $(UTILS_DOLLAR_SRC:.c=.o)
OBJ_DIR_UTILS_DOLLAR = $(addprefix $(OBJ_DIR), $(OBJ_UTILS_DOLLAR))

OBJ_UTILS_SYNTAX   = $(UTILS_SYNTAX_SRC:.c=.o)
OBJ_DIR_UTILS_SYNTAX = $(addprefix $(OBJ_DIR), $(OBJ_UTILS_SYNTAX))

OBJ_ECHO    = $(ECHO_SRC:.c=.o)
OBJ_DIR_ECHO = $(addprefix $(OBJ_DIR), $(OBJ_ECHO))

OBJ_PARSING		= $(PARSING_SRC:.c=.o)
OBJ_DIR_PARSING	= $(addprefix $(OBJ_DIR), $(OBJ_PARSING))

OBJ_PARSING_TOKEN = $(PARSING_TOKEN_SRC:.c=.o)
OBJ_DIR_PARSING_TOKEN = $(addprefix $(OBJ_DIR), $(OBJ_PARSING_TOKEN))

LIBFTDIR    = lib
LIBFT       = $(LIBFTDIR)/libft.a

#================RULES================

all: ${NAME}
	@echo "\n./minishell a été créé. 💯\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(BUILT_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(EXEC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(UTILS_PRINT_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(UTILS_FREE_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(UTILS_CREATE_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(UTILS_DOLLAR_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(UTILS_SYNTAX_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(UTILS_DUP_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(ECHO_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(PARSING_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(PARSING_TOKEN_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

${NAME}: $(LIBFT) $(OBJ_DIR_SRC) $(OBJ_DIR_BUILD) $(OBJ_DIR_ECHO) $(OBJ_DIR_EXEC) $(OBJ_DIR_PARSING) $(OBJ_DIR_PARSING_TOKEN) $(OBJ_DIR_UTILS_SYNTAX) $(OBJ_DIR_UTILS_DUP) $(OBJ_DIR_UTILS_DOLLAR) $(OBJ_DIR_UTILS_FREE) $(OBJ_DIR_UTILS_PRINT) $(OBJ_DIR_UTILS_CREATE)
	$(CC) $(CFLAGS) $(OBJ_DIR_SRC) $(OBJ_DIR_BUILD) $(OBJ_DIR_EXEC) $(OBJ_DIR_ECHO) $(OBJ_DIR_PARSING) $(OBJ_DIR_UTILS_SYNTAX) $(OBJ_DIR_PARSING_TOKEN) $(OBJ_DIR_UTILS_DUP) $(OBJ_DIR_UTILS_DOLLAR) $(OBJ_DIR_UTILS_FREE) $(OBJ_DIR_UTILS_PRINT) $(OBJ_DIR_UTILS_CREATE) $(LIBFT) -o $@ $(INC) -lreadline

$(LIBFT):
	@make -C libft

-include $(OBJ_DIR_SRC:.o=.d)
-include $(OBJ_DIR_BUILD:.o=.d)
-include $(OBJ_DIR_EXEC:.o=.d)
-include $(OBJ_DIR_UTILS_FREE:.o=.d)
-include $(OBJ_DIR_UTILS_PRINT:.o=.d)
-include $(OBJ_DIR_UTILS_CREATE:.o=.d)
-include $(OBJ_DIR_UTILS_DOLLAR:.o=.d)
-include $(OBJ_DIR_UTILS_DUP:.o=.d)
-include $(OBJ_DIR_UTILS_SYNTAX:.o=.d)
-include $(OBJ_DIR_ECHO:.o=.d)
-include $(OBJ_DIR_PARSING:.o=.d)
-include $(OBJ_DIR_PARSING_TOKEN:.o=.d)

clean:
	@rm -rf ${OBJ_DIR}
	@make -C libft clean > /dev/null 2>&1
	@echo "\nObjets : 🗑️\n"

fclean: clean
	@rm -rf ${NAME}
	@make -C libft fclean > /dev/null 2>&1
	@echo "./minishell et les objets : 🗑️\n"

re: fclean all

run: $(NAME)
	@clear
	@./minihell

run_v: $(NAME)
	@clear
	@valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=trash.supp ./minihell

push: fclean
	@git add .
	@git commit -m "VOIR README"
	@git push

.PHONY: all clean fclean re