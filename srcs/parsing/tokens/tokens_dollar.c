/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:44:13 by glions            #+#    #+#             */
/*   Updated: 2024/07/16 15:23:22 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokens_dollar2(t_dt_elem **token, t_check *check, char *str, int *j)
{
	char	*res;

	if (ft_isalnum(str[1]) == 1)
	{
		if (var_dollar(str + 1, j, &res) == 0)
			return (0);
		if (check->curr_state == IN_DQUOTE)
			(*j)++;
		*token = create_dt_elem(res, ENV, check->curr_state);
	}
	return (1);
}

int	tokens_dollar(char *str, t_dt_elem **token, t_check *check, int *j)
{
	int		k;

	if (check->curr_state == IN_QUOTE)
	{
		k = 0;
		while (str[k++] != '\'')
			*token = create_dt_elem(ft_strndup(str, k), WORD,
					check->curr_state);
		*j += k - 2;
	}
	else
		if (tokens_dollar2(token, check, str, j) == 0)
			return (0);
	return (1);
}
