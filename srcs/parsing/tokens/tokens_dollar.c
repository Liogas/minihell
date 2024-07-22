/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 06:11:05 by glions            #+#    #+#             */
/*   Updated: 2024/07/22 11:33:29 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_value(char *str, t_minish *dt_minish, int *k)
{
	char	*value;

	value = malloc(sizeof(char *));
	value[0] = 0;
	while (str[k])
	{
		if (str[k] == '$' && token->state != IN_QUOTE && token->value[k
			+ 1] && (isalpha(str[k + 1]) || token->value[k
				+ 1] == '?'))
		{
			if (!add_dollar(&value, &k, token, dt_minish))
				return (NULL);
		}
		else if (!add_normal(&value, &k, token))
			return (NULL);
	}
	return (value);
}

int	tokens_dollar(char *str, t_dt_elem **token, t_minish *dt_minish, int *j)
{
	int		k;
	char	*res;

	if (dt_minish->check->curr_state == IN_QUOTE)
	{
		k = 0;
		while (str[k] != '\'')
			k++;
		*token = create_dt_elem(ft_strndup(str, k), WORD,
			dt_minish->check->curr_state);
		*j += k - 2;
	}
	else if (ft_isalnum(str[1]) == 1)
	{
		k = 1;
		res = get_value(str + 1, dt_minish, &k);
		if (!res)
			return (0);
		if (dt_minish->check->curr_state == IN_DQUOTE)
			(*j)++;
		*token = create_dt_elem(res, ENV, dt_minish->check->curr_state);
	}
	return (1);
}
