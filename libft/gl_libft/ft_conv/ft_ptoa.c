/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:52:01 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:32:20 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

static unsigned int	ft_ptoa_len(long long n)
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

static char	*ft_ptoa_max(void)
{
	char	*s;

	s = malloc(12 * sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, "0xffffffffffffffff", 11);
	return (s);
}

char	*ft_ptoa(unsigned long long p)
{
	char	*s;
	int		i;
	int		j;
	int		tmp;

	if (p == ULONG_MAX - 1)
		return (ft_ptoa_max());
	i = ft_ptoa_len(p) + 2;
	s = (char *)malloc((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	j = i;
	s[0] = '0';
	s[1] = 'x';
	while (--j > 1)
	{
		tmp = p % 16;
		if (tmp < 10)
			s[j] = tmp + '0';
		else
			s[j] = tmp + 87;
		p /= 16;
	}
	s[i] = '\0';
	return (s);
}
