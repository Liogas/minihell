/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:39:47 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:32:53 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

void	ft_putnbr_u_fd(unsigned int n, int fd)
{
	if (n == 0xffffffff)
		ft_putstr_fd("4294967295", fd);
	if (n < 10)
		ft_putchar_fd(n + '0', fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd((n % 10) + '0', fd);
	}
}
