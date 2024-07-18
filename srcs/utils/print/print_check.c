/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:11:09 by glions            #+#    #+#             */
/*   Updated: 2024/07/18 12:08:47 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_check(t_check *dt)
{
	int	i;

	i = -1;
	printf("BUILTIN :\n");
	while (dt->bltn[++i])
		printf("[%d] : |%s|\n", i, dt->bltn[i]);
	i = -1;
	printf("OPRT :\n");
	while (dt->oprt[++i])
		printf("[%d] : <%s>\n", i, dt->oprt[i]);
	i = -1;
	printf("REDIRCT :\n");
	while (dt->redirct[++i])
		printf("[%d] : |%s|\n", i, dt->redirct[i]);
	i = -1;
	printf("PATHS :\n");
	while (dt->paths[++i])
		printf("[%d] : |%s|\n", i, dt->paths[i]);
}
