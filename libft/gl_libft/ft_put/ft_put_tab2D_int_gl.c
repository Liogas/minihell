/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_tab2D_int_gl.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:56:57 by glions            #+#    #+#             */
/*   Updated: 2024/04/25 14:41:57 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

void	ft_put_tab2d_int_gl(int **tab, int height, int width)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			(ft_putnbr_fd(tab[i][j], 1), ft_putchar_fd(' ', 1));
		ft_putchar_fd('\n', 1);
	}
}
