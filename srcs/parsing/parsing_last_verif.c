/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_last_verif.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:03:10 by glions            #+#    #+#             */
/*   Updated: 2024/07/16 15:41:35 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	last_verif_operator(t_dt_elem *next)
{
	while (next && next->type == WHITE_SPACE)
		next = next->next;
	if (!next)
		return (0);
	else if (next->type == BLOCK || type_is_redir(next->type)
		|| type_accept_for_quote(next->type))
		return (1);
	return (0);
}

static int	last_verif_redir(t_dt_elem *next)
{
	while (next && next->type == WHITE_SPACE)
		next = next->next;
	if (!next)
		return (0);
	else if (type_accept_for_quote(next->type))
		return (1);
	return (0);
}

static int	parsing_remove_whitespace(t_dt_elem **tokens, t_dt_elem *tmp,
		t_dt_elem *token)
{
	while (*tokens && (*tokens)->type == WHITE_SPACE)
		*tokens = (*tokens)->next;
	token = *tokens;
	while (token)
	{
		tmp = NULL;
		if (token->type == BLOCK)
		{
			if (parsing_remove_whitespace(&token->content, tmp, token) == 0)
				return (0);
		}
		else if (token->type == WHITE_SPACE)
		{
			tmp = token->next;
			if (remove_dt_elem(tokens, &token) == 0)
				return (0);
			token = NULL;
		}
		if (!tmp && token)
			token = token->next;
		else
			token = tmp;
	}
	return (1);
}

int	parsing_last_verif(t_dt_elem **tokens)
{
	t_dt_elem	*token;

	token = *tokens;
	while (token)
	{
		if (type_is_operator(token->type))
		{
			if (last_verif_operator(token->next) == 0)
				return (0);
		}
		else if (type_is_redir(token->type))
		{
			if (last_verif_redir(token->next) == 0)
				return (0);
		}
		token = token->next;
	}
	return (parsing_remove_whitespace(tokens, NULL, NULL));
}
