/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:54:07 by glions            #+#    #+#             */
/*   Updated: 2024/07/22 18:43:55 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_cmd2(char *str, t_minish *dt_minish, int *j, t_dt_elem **token)
{
	if (ft_strncmp(str + *j, "<<", 2) == 0 || ft_strncmp(str + *j, "<", 1) == 0
		|| ft_strncmp(str + *j, ">>", 2) == 0 || ft_strncmp(str + *j, ">",
			1) == 0)
	{
		if (tokens_redir(str + *j, token, dt_minish->check, j) == 0)
			return (printf("ERROR 4\n"), 0);
	}
	else if (is_white(str[*j]) == 1)
	{
		if (token_whitespace(str, token, dt_minish->check, *j) == 0)
			return (printf("ERROR 5\n"), 0);
	}
	else
	{
		if (token_word(str + *j, token, dt_minish, j) == 0)
			return (printf("ERROR 6\n"),0);
	}
	return (1);
}

int	new_cmd(char *str, t_minish *dt_minish, int *i, t_dt_elem **curr_block)
{
	int			j;
	t_dt_elem	*token;

	j = 0;
	while (str[j] && is_operator(str + j) == 0)
	{
		if (str[j] == '\"' || str[j] == '\'')
		{
			if (token_quotes(str + j, &token, dt_minish->check, str[j]) == 0)
				return (0);
		}
		else if (new_cmd2(str, dt_minish, &j, &token) == 0)
			return (printf("ERROR 2\n"), 0);
		if (!add_back_elem(curr_block, token))
			return (printf("ERROR 1\n"), 0);
		j++;
	}
	(*i) += j - 1;
	return (1);
}
