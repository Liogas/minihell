/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:43:47 by glions            #+#    #+#             */
/*   Updated: 2024/04/13 17:50:43 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

t_next_line	*free_element(t_next_line *e, t_next_line *l)
{
	t_next_line	*tmp;
	t_next_line	*previous;

	if (l == NULL)
		return (l);
	previous = l;
	if (previous->fd == e->fd)
	{
		l = previous->next;
		free(previous);
		return (l);
	}
	tmp = previous->next;
	while (tmp != NULL)
	{
		if (tmp->fd == e->fd)
		{
			previous->next = tmp->next;
			free(tmp);
			return (l);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (l);
}

t_next_line	*get_element(t_next_line **l, int fd)
{
	t_next_line	*e;
	t_next_line	*tmp;

	tmp = NULL;
	if (*l)
	{
		tmp = *l;
		while (tmp && tmp->fd != fd)
			tmp = tmp->next;
	}
	if (!tmp)
	{
		e = malloc(sizeof(t_next_line));
		if (!e)
			return (NULL);
		e->fd = fd;
		e->finish = 0;
		e->mem = NULL;
		e->next = *l;
		*l = e;
	}
	else
		e = tmp;
	return (e);
}

int	new_line_in(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*setup_mem(char *m, char *l)
{
	char	*new_m;
	int		i;
	int		j;

	if (ft_strlen(l) >= ft_strlen(m))
		return (free(m), (NULL));
	new_m = malloc((ft_strlen(m) - ft_strlen(l) + 1) * sizeof(char));
	if (!new_m)
		return (free(m), (NULL));
	i = ft_strlen(l);
	j = 0;
	while (m[i] != '\0')
		new_m[j++] = m[i++];
	new_m[j] = 0;
	free(m);
	return (new_m);
}
