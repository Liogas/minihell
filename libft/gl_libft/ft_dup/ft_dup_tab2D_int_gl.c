/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_tab2D_int_gl.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:18:01 by glions            #+#    #+#             */
/*   Updated: 2024/04/25 14:41:27 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

int	**ft_dup_tab2d_int_gl(int **target, int height, int width)
{
	int	**tab;
	int	i;
	int	j;

	tab = malloc(height * sizeof(int *));
	if (!tab)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		tab[i] = malloc(width * sizeof(int));
		if (!tab[i])
			return (ft_free_tab2d_int_gl(tab, height), NULL);
		j = -1;
		while (++j < width)
			tab[i][j] = target[i][j];
	}
	return (tab);
}
