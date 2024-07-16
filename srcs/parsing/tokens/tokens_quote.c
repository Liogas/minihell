/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:08:12 by glions            #+#    #+#             */
/*   Updated: 2024/07/16 15:43:57 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_dquote(char *str, t_dt_elem **token, t_check *check)
{
	enum e_type	type;

	type = DOUBLE_QUOTE;
	if (check->curr_state == IN_QUOTE)
	{
		type = WORD;
		*token = create_dt_elem(ft_strndup(str, 1), type, check->curr_state);
	}
	else if (check->curr_state == IN_DQUOTE)
	{
		check->curr_state = GENERAL;
		*token = create_dt_elem(ft_strndup(str, 1), type, check->curr_state);
	}
	else
	{
		*token = create_dt_elem(ft_strndup(str, 1), type, check->curr_state);
		check->curr_state = IN_DQUOTE;
	}
	if (!*token)
		return (0);
	return (1);
}

int	token_quote(char *str, t_dt_elem **token, t_check *check)
{
	enum e_type	type;

	type = QUOTE;
	if (check->curr_state == IN_DQUOTE)
	{
		type = WORD;
		*token = create_dt_elem(ft_strndup(str, 1), type, check->curr_state);
	}
	else if (check->curr_state == IN_QUOTE)
	{
		check->curr_state = GENERAL;
		*token = create_dt_elem(ft_strndup(str, 1), type, check->curr_state);
	}
	else
	{
		*token = create_dt_elem(ft_strndup(str, 1), type, check->curr_state);
		check->curr_state = IN_QUOTE;
	}
	if (!*token)
		return (0);
	return (1);
}

int	token_quotes(char *str, t_dt_elem **token, t_check *check, char c)
{
	if (c == '\'')
		return (token_quote(str, token, check));
	else
		return (token_dquote(str, token, check));
}
