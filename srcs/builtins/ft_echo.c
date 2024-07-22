/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:45:33 by glions            #+#    #+#             */
/*   Updated: 2024/07/22 06:03:49 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	simple_quote(char *str, t_echo *dt, int *i)
{
	while (str[++(*i)] && str[*i] != '\'')
		printf("%c", str[(*i)]);
	dt->nb_simple--;
}

static int	double_quote(char *str, t_echo *dt, int *i)
{
	while (str[++(*i)] && str[*i] != '\"')
	{
		if (str[*i] == '$')
		{
			return (0);
		}
		else
			printf("%c", str[*i]);
	}
	dt->nb_double--;
	return (1);
}

int	ft_echo(char *str, int nl)
{
	int		i;
	t_echo	dt;

	dt.parenthese = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			simple_quote(str, &dt, &i);
		else if (str[i] == '\"')
		{
			if (!double_quote(str + i, &dt, &i))
				return (0);
		}
		else if (str[i] == '$')
		{
			return (0);
		}
		else
			printf("%c", str[i]);
	}
	if (nl)
		printf("\n");
	return (1);
}
