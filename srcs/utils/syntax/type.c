/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:59:42 by glions            #+#    #+#             */
/*   Updated: 2024/06/25 12:26:54 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_is_redir(enum e_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT || type == HERE_DOC_IN
		|| type == HERE_DOC_OUT)
		return (1);
	return (0);
}

int	type_is_operator(enum e_type type)
{
	if (type == PIPE_LINE || type == OR || type == AND)
		return (1);
	return (0);
}

int	type_is_quote(enum e_type type)
{
	if (type == DOUBLE_QUOTE || type == QUOTE)
		return (1);
	return (0);
}

int	type_accept_for_quote(enum e_type type)
{
	if (type == CALCUL || type == WORD || type == ENV || type_is_quote(type))
		return (1);
	return (0);
}
