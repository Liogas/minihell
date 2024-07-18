/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:25:01 by glions            #+#    #+#             */
/*   Updated: 2024/07/18 16:00:10 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_whitespace(char *str, t_dt_elem **token, t_check *check, int j)
{
	enum e_type	type;

	if (check->curr_state == IN_DQUOTE || check->curr_state == IN_QUOTE)
		type = WORD;
	else
		type = WHITE_SPACE;
	*token = create_dt_elem(ft_strndup(str + j, 1), type, check->curr_state);
	if (!*token)
		return (0);
	return (1);
}

int	token_word(char *str, t_dt_elem **token, t_check *check, int *j)
{
	int	k;
	int	d;

	k = 0;
	d = 0;
	while (str[k + *j])
	{
		if ((check->curr_state != IN_QUOTE && str[k + *j] == '\"')
			|| (check->curr_state != IN_DQUOTE && str[k + *j] == '\'')
				|| (check->curr_state == GENERAL && (is_operator(str + k + *j)
				|| is_white(str[k + *j]))))
			break ;
		if (str[k + *j] == '$')
			d = 1;
		else if (d && is_white(k + *j))
			d = 0;
		else if (d && isalnum(str[k + *j]) == 0 && str[k + *j] != '?')
			return (printf("ERROR 7\n"), 0);
		k++;
	}
	*token = create_dt_elem(ft_strndup(str + *j, k), WORD, check->curr_state);
	if (!*token)
		return (printf("ERROR 8\n"), 0);
	*j += k - 1;
	return (1);
}
