/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:36:45 by glions            #+#    #+#             */
/*   Updated: 2024/06/04 10:42:55 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_file.h"

void	free_file_gl(t_file_gl *file)
{
	close(file->fd);
	if (file)
		free_list_gl(&file->lines, free);
	free(file);
}

t_file_gl	*new_file_gl(char *pathfile, int __oflag)
{
	t_file_gl	*new;

	new = malloc(sizeof(t_file_gl));
	if (!new)
		return (NULL);
	new->pathfile = pathfile;
	new->fd = open(pathfile, __oflag);
	if (new->fd < 0)
		return (free(new), (NULL));
	new->lines = NULL;
	new->nblines = 0;
	return (new);
}

int	read_nextline_file_gl(t_file_gl *file)
{
	char	*line;

	line = get_next_line(file->fd);
	if (!line)
		return (0);
	addback_list_gl(&file->lines, new_element_gl(line));
	file->nblines += 1;
	return (1);
}

void	read_all_file_gl(t_file_gl *file)
{
	int		while_state;

	while_state = 1;
	while (while_state)
		while_state = read_nextline_file_gl(file);
}
