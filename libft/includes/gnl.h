/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:23:45 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:36:02 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "gl_libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

typedef struct s_next_line
{
	char				*mem;
	int					fd;
	int					finish;
	struct s_next_line	*next;
}	t_next_line;

char		*get_next_line(int fd);
char		*setup_mem(char *m, char *l);
int			new_line_in(const char *s);
t_next_line	*get_element(t_next_line **l, int fd);
t_next_line	*free_element(t_next_line *e, t_next_line *l);

#endif