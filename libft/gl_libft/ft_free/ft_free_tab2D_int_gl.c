/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab2D_int_gl.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:59:03 by glions            #+#    #+#             */
/*   Updated: 2024/04/25 14:41:40 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

void	ft_free_tab2d_int_gl(int **tab, int height)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (i < height && tab[i])
		free(tab[i++]);
	free(tab);
}
