/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_file.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:29:11 by glions            #+#    #+#             */
/*   Updated: 2024/06/04 10:46:17 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_FILE_H
# define GL_FILE_H

# include "gl_libft.h"
# include "gl_list.h"
# include "gnl.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_file_gl
{
	char		*pathfile;
	int			fd;
	t_list_gl	*lines;
	int			nblines;
}				t_file_gl;

t_file_gl		*new_file_gl(char *pathfile, int __oflag);
void			free_file_gl(t_file_gl *file);
int				read_nextline_file_gl(t_file_gl *file);
void			read_all_file_gl(t_file_gl *file);

#endif