/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:51:37 by glions            #+#    #+#             */
/*   Updated: 2024/07/15 16:18:59 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_heredoc(t_dt_elem **token, t_check *check, char *str, int *j)
{
	enum e_type	type;

	if (check->curr_state == IN_DQUOTE || check->curr_state == IN_QUOTE)
		type = WORD;
	else
		type = HERE_DOC_IN;
	*token = create_dt_elem(ft_strndup(str, 2), type, check->curr_state);
	if (!*token)
		return (0);
	(*j)++;
	return (1);
}

static int	token_in(t_dt_elem **token, t_check *check, char *str)
{
	enum e_type	type;

	if (check->curr_state == IN_DQUOTE || check->curr_state == IN_QUOTE)
		type = WORD;
	else
		type = REDIR_IN;
	*token = create_dt_elem(ft_strndup(str, 1), type, check->curr_state);
	if (!*token)
		return (0);
	return (1);
}

static int	token_out_append(t_dt_elem **token, t_check *check, char *str,
		int *j)
{
	enum e_type	type;

	if (check->curr_state == IN_DQUOTE || check->curr_state == IN_QUOTE)
		type = WORD;
	else
		type = HERE_DOC_OUT;
	*token = create_dt_elem(ft_strndup(str, 2), type, check->curr_state);
	if (!*token)
		return (0);
	(*j)++;
	printf("dddd");
	return (1);
}

static int	token_out(t_dt_elem **token, t_check *check, char *str)
{
	enum e_type	type;

	if (check->curr_state == IN_DQUOTE || check->curr_state == IN_QUOTE)
		type = WORD;
	else
		type = REDIR_OUT;
	*token = create_dt_elem(ft_strndup(str, 1), type, check->curr_state);
	if (!*token)
		return (0);
	return (1);
}

int	tokens_redir(char *str, t_dt_elem **token, t_check *check, int *j)
{
	// printf("Je rentre dans token_redir avec->|%s|\n", str);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (token_heredoc(token, check, str, j));
	else if (ft_strncmp(str, "<", 1) == 0)
		return (token_in(token, check, str));
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (token_out_append(token, check, str, j));
	else
		return (token_out(token, check, str));
}
