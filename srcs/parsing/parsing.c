/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:19:36 by glions            #+#    #+#             */
/*   Updated: 2024/07/22 13:20:58 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_syntax(t_check *check)
{
	check->nb_double = 0;
	check->nb_single = 0;
}

static int	blockenisation2(int *i, t_dt_elem **curr_block, t_minish *dt,
		char *str)
{
	char	c;

	c = str[*i];
	if (accept_char(c) == 1)
	{
		if (new_cmd(str + *i, dt, i, curr_block) == 0)
			return (printf("ERROR 3\n"), 0);
	}
	else
		return (0);
	return (1);
}

int	blockenisation(t_dt_elem **curr_block, char *str, t_minish *dt)
{
	int		i;
	char	c;
	int		e;

	i = 0;
	while (str[i])
	{
		c = str[i];
		e = check_operator(str + i, dt->check, curr_block);
		if (e == 0)
			return (0);
		else if (e == -1 && is_white(c) == 1)
		{
			if (add_back_elem(curr_block, create_dt_elem(ft_strndup(str + i, 1),
						WHITE_SPACE, GENERAL)) == 0)
				return (0);
		}
		else if (e == -1 && blockenisation2(&i, curr_block, dt, str) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	parsing(t_minish *dt)
{
	reset_syntax(dt->check);
	if (parsing_syntax(dt->check) == 0)
		return (0);
	if (blockenisation(&dt->block_token, dt->check->line_cmd, dt) == 0)
		return (0);
	if (parsing_quote(&dt->block_token) == 0)
		return (0);
	if (parsing_last_verif(&dt->block_token) == 0)
		return (0);
	return (1);
}
