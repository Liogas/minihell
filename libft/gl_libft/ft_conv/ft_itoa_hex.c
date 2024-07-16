/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:55:21 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:32:24 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

static unsigned int	ft_itoa_hex_len(unsigned int n)
{
	unsigned int		i;
	unsigned long long	m;

	i = 1;
	m = 1;
	while (n / m >= 16)
	{
		m *= 16;
		i++;
	}
	return (i);
}

char	*ft_itoa_hex(unsigned int n)
{
	char	*s;
	int		i;
	int		j;
	int		tmp;

	i = ft_itoa_hex_len(n);
	s = (char *)malloc((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	j = i;
	while (--j >= 0)
	{
		tmp = n % 16;
		if (tmp < 10)
			s[j] = tmp + '0';
		else
			s[j] = tmp + 87;
		n /= 16;
	}
	s[i] = '\0';
	return (s);
}
