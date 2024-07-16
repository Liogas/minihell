/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:53:04 by glions            #+#    #+#             */
/*   Updated: 2024/06/26 12:30:27 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strjoin_quote(t_dt_elem **base, t_dt_elem *list)
{
	t_dt_elem	*tmp;

	while (list && (list->state == IN_QUOTE || list->state == IN_DQUOTE
			|| type_accept_for_quote(list->type)))
	{
		if (list->type != DOUBLE_QUOTE && list->type != QUOTE)
		{
			(*base)->value = ft_strjoin_w_free((*base)->value, list->value);
			if (!(*base)->value)
				return (0);
		}
		tmp = list->next;
		if (!remove_dt_elem(base, &list))
			return (0);
		list = tmp;
	}
	return (1);
}

static int	start_parsing(t_dt_elem **start)
{
	t_dt_elem	*base;

	base = *start;
	if (strjoin_quote(&base, base->next) == 0)
		return (0);
	return (1);
}

int	has_job(t_dt_elem *token)
{
	while (token)
	{
		if (token->type == CALCUL || token->type == ENV || token->type == WORD)
			return (1);
		else if (type_is_quote(token->type))
			token = token->next;
		else
			break ;
	}
	return (printf("Sortie 2\n"), 0);
}

static int	parsing_quote2(t_dt_elem *token)
{
	if (token->content)
	{
		if (parsing_quote(&token->content) == 0)
			return (0);
	}
	else if (!type_is_operator(token->type) && !type_is_redir(token->type)
		&& !token->content && token->next && (type_is_quote(token->next->type)
			&& !type_is_quote(token->type)) && !is_white((token->value)[0]))
	{
		if (start_parsing(&token) == 0)
			return (0);
	}
	return (1);
}

int	parsing_quote(t_dt_elem **tokens)
{
	t_dt_elem	*token;
	t_dt_elem	*tmp;

	token = *tokens;
	while (token)
	{
		if (type_is_quote(token->type) && has_job(token))
		{
			while (token->type == DOUBLE_QUOTE || token->type == QUOTE)
			{
				tmp = token->next;
				remove_dt_elem(tokens, &token);
				token = tmp;
			}
			if (start_parsing(&token) == 0)
				return (0);
		}
		else if (parsing_quote2(token) == 0)
			return (0);
		token = token->next;
	}
	return (1);
}
