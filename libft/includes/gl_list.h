/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:02:31 by glions            #+#    #+#             */
/*   Updated: 2024/06/04 10:47:38 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_LIST_H
# define GL_LIST_H

# include "gl_utils.h"

typedef struct s_list_gl
{
	void				*content;
	struct s_list_gl	*next;
}						t_list_gl;

t_list_gl				*new_element_gl(void *content);

void					free_list_gl(t_list_gl **list, void (*del)(void *));
void					free_element_gl(t_list_gl **list, void (*del)(void *),
							t_list_gl *element);
int						addback_list_gl(t_list_gl **list, t_list_gl *element);
int						addfront_list_gl(t_list_gl **list, t_list_gl *element);
int						addafter_list_gl(t_list_gl **before,
							t_list_gl *element);
int						addbefore_list_gl(t_list_gl **list, t_list_gl *after,
							t_list_gl *element);

#endif