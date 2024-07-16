INCLUDES		=	-I./includes/

PATH_LIBFT		=	./gl_libft/
SRCS_LIBFT		=	$(PATH_LIBFT)ft_char/ft_isalpha.c $(PATH_LIBFT)ft_char/ft_isdigit.c $(PATH_LIBFT)ft_char/ft_isalnum.c $(PATH_LIBFT)ft_char/ft_isascii.c \
					$(PATH_LIBFT)ft_char/ft_isprint.c $(PATH_LIBFT)ft_char/ft_toupper.c $(PATH_LIBFT)ft_char/ft_tolower.c \
\
					$(PATH_LIBFT)ft_mem/ft_memset.c $(PATH_LIBFT)ft_mem/ft_bzero.c $(PATH_LIBFT)ft_mem/ft_memcpy.c $(PATH_LIBFT)ft_mem/ft_memmove.c \
					$(PATH_LIBFT)ft_mem/ft_memchr.c $(PATH_LIBFT)ft_mem/ft_memcmp.c \
\
					$(PATH_LIBFT)ft_str/ft_strlcpy.c $(PATH_LIBFT)ft_str/ft_strlcat.c $(PATH_LIBFT)ft_str/ft_strlen.c $(PATH_LIBFT)ft_str/ft_strchr.c \
					$(PATH_LIBFT)ft_str/ft_strrchr.c $(PATH_LIBFT)ft_str/ft_strncmp.c $(PATH_LIBFT)ft_str/ft_strcmp.c $(PATH_LIBFT)ft_str/ft_strnstr.c \
					$(PATH_LIBFT)ft_str/ft_strupper.c $(PATH_LIBFT)ft_str/ft_strdup.c $(PATH_LIBFT)ft_str/ft_strndup.c $(PATH_LIBFT)ft_str/ft_substr.c \
					$(PATH_LIBFT)ft_str/ft_strjoin.c $(PATH_LIBFT)ft_str/ft_constr.c $(PATH_LIBFT)ft_str/ft_strtrim.c $(PATH_LIBFT)ft_str/ft_split.c \
					$(PATH_LIBFT)ft_str/ft_strmapi.c $(PATH_LIBFT)ft_str/ft_striteri.c \
\
					$(PATH_LIBFT)ft_free/ft_free_tab2D_int_gl.c \
\
					$(PATH_LIBFT)ft_conv/ft_atoi.c $(PATH_LIBFT)ft_conv/ft_itoa.c $(PATH_LIBFT)ft_conv/ft_utoa.c $(PATH_LIBFT)ft_conv/ft_ptoa.c \
					$(PATH_LIBFT)ft_conv/ft_itoa_hex.c \
\
					$(PATH_LIBFT)ft_dup/ft_dup_tab2D_int_gl.c \
\
					$(PATH_LIBFT)ft_put/ft_putchar_fd.c $(PATH_LIBFT)ft_put/ft_putstr_fd.c $(PATH_LIBFT)ft_put/ft_putendl_fd.c $(PATH_LIBFT)ft_put/ft_putnbr_fd.c \
					$(PATH_LIBFT)ft_put/ft_putnbr_u_fd.c $(PATH_LIBFT)ft_put/ft_putnbr_hex_fd.c $(PATH_LIBFT)ft_put/ft_putptr_hex_fd.c $(PATH_LIBFT)ft_put/ft_put_tab2D_int_gl.c\
\
					$(PATH_LIBFT)ft_alloc/ft_calloc.c
OBJS_LIBFT		=	$(SRCS_LIBFT:.c=.o)

PATH_GNL		=	./gl_gnl/
SRCS_GNL		=	$(PATH_GNL)gnl_utils.c $(PATH_GNL)gnl.c
OBJS_GNL		=	$(SRCS_GNL:.c=.o)

PATH_LIST		=	./gl_list/
SRCS_LIST		=	$(PATH_LIST)add_list_gl.c $(PATH_LIST)free_list_gl.c $(PATH_LIST)new_element_gl.c
OBJS_LIST		=	$(SRCS_LIST:.c=.o)

PATH_FILE		=	./gl_file/
SRCS_FILE		=	$(PATH_FILE)gl_file.c
OBJS_FILE		=	$(SRCS_FILE:.c=.o)

PATH_UTILS		=	./gl_utils/
SRCS_UTILS		=	$(PATH_UTILS)verif_extension.c
OBJS_UTILS		=	$(SRCS_UTILS:.c=.o)

OBJS_LIB		=	$(OBJS_LIBFT) $(OBJS_GNL) $(OBJS_LIST) $(OBJS_FILE) $(OBJS_UTILS)
CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra
AR				=	ar -rcs
LIB				=	../lib/libft.a


all : $(LIB)

%.o: %.c
	@$(CC) $(CFLAGS) -g3 -o $@ -c $^ $(INCLUDES)

$(LIB): $(OBJS_LIB)
	@echo "LIBFT    ❌"
	@mkdir -p ../lib
	@$(AR) $(LIB) $(OBJS_LIB)
	@echo "LIBFT    ✅"


clean:
	@rm -f $(OBJS_LIB)

fclean: clean
	@rm -drf ../lib
	@rm -f $(LIB)
	@echo "LIBFT    ❌"

re: fclean $(LIB)

.phony: all re clean fclean
