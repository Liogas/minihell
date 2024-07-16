/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:02:18 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:32:08 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	v;

	i = 0;
	n = 1;
	v = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			n = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		v *= 10;
		v += nptr[i] - '0';
		i++;
	}
	return (v * n);
}

int	ft_atoin(const char *nptr, int end)
{
	int	i;
	int	n;
	int	v;

	i = 0;
	n = 1;
	v = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			n = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]) && i < end)
	{
		v *= 10;
		v += nptr[i] - '0';
		i++;
	}
	return (v * n);
}
