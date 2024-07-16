/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:23:03 by glions            #+#    #+#             */
/*   Updated: 2024/04/13 17:50:38 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static char	*add_mem(char *m, char *b)
{
	char	*new_m;
	int		i;
	int		j;

	if (!b || !b[0])
		return (m);
	new_m = malloc((ft_strlen(m) + ft_strlen(b) + 1) * sizeof(char));
	if (!new_m)
	{
		if (m)
			free(m);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (m && m[i] != '\0')
		new_m[j++] = m[i++];
	i = 0;
	while (b && b[i] != '\0')
		new_m[j++] = b[i++];
	new_m[j] = 0;
	if (m)
		free(m);
	return (new_m);
}

static char	*get_line(char **m)
{
	int		i;
	char	*line;

	if (!(*m))
		return (NULL);
	i = 0;
	while ((*m)[i] != '\0' && (*m)[i] != '\n')
		i++;
	if ((*m)[i] == '\n')
		line = malloc((i + 2) * sizeof(char));
	else
		line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while ((*m)[i] != '\0' && (*m)[i] != '\n')
	{
		line[i] = (*m)[i];
		i++;
	}
	if ((*m)[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	*m = setup_mem(*m, line);
	return (line);
}

static int	read_file(t_next_line **e)
{
	int		size;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	size = read((*e)->fd, buffer, BUFFER_SIZE);
	if (size < 0)
		return (free(buffer), (-1));
	buffer[size] = 0;
	(*e)->mem = add_mem((*e)->mem, buffer);
	if (size == 0)
		(*e)->finish = 1;
	if ((*e)->finish || new_line_in((*e)->mem) > 0)
		return (free(buffer), (0));
	return (free(buffer), (1));
}

static char	*read_next_line(t_next_line **e)
{
	char	*line;
	int		r_read_file;

	line = NULL;
	if (!(*e)->mem && (*e)->finish)
		return (NULL);
	if (new_line_in((*e)->mem) != -1 || (*e)->finish)
	{
		line = get_line(&(*e)->mem);
		return (line);
	}
	r_read_file = 1;
	while (r_read_file > 0 && !(*e)->finish)
	{
		r_read_file = read_file(e);
		if (r_read_file == -1)
			return (NULL);
	}
	line = get_line(&(*e)->mem);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_next_line	*list;
	t_next_line			*element;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	element = get_element(&list, fd);
	if (!element)
		return (NULL);
	line = read_next_line(&element);
	if (!line || (line && !element->mem && element->finish))
		list = free_element(element, list);
	return (line);
}
