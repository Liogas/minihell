/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:49:39 by lbegliom          #+#    #+#             */
/*   Updated: 2024/07/16 15:18:23 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	var_dollar(char *str, int *i, char **res_env)
{
	char	*variable;
	int		k;
	int		j;

	j = 0;
	while (str[j] && str[j] != ' ' && str[j] != '\"')
	{
		if (ft_isalnum(str[j]) == 0)
			return (0);
		j++;
	}
	(*i) += j;
	variable = malloc((j + 1) * sizeof(char));
	if (!variable)
		return (0);
	k = -1;
	while (++k < j && str[k])
		variable[k] = str[k];
	variable[k] = '\0';
	*res_env = getenv(variable);
	free(variable);
	return (1);
}
