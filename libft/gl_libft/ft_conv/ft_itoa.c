/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:56:56 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:32:16 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

static int	ft_itoa_len(int n)
{
	int	i;
	int	m;

	i = 1;
	m = 1;
	while (n / m >= 10)
	{
		m *= 10;
		i++;
	}
	return (i);
}

static char	*ft_itoa_min_max(int max)
{
	char	*s;
	char	*s_cpy;

	if (!max)
	{
		s = malloc(12 * sizeof(char));
		if (!s)
			return (NULL);
		s_cpy = "-2147483648";
		ft_strlcpy(s, s_cpy, 12);
	}
	else
	{
		s = malloc(11 * sizeof(char));
		if (!s)
			return (NULL);
		s_cpy = "2147483647";
		ft_strlcpy(s, s_cpy, 11);
	}
	return (s);
}

static char	*ft_itoa_ne(int n)
{
	char	*s;
	int		i;
	int		j;

	n *= -1;
	i = ft_itoa_len(n) + 1;
	s = (char *)malloc((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[0] = '-';
	j = i;
	while (--j > 0)
	{
		s[j] = (n % 10) + '0';
		n /= 10;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		j;

	if (n == -2147483648)
		return (ft_itoa_min_max(0));
	else if (n == 2147483647)
		return (ft_itoa_min_max(1));
	if (n < 0)
		return (ft_itoa_ne(n));
	i = ft_itoa_len(n);
	s = (char *)malloc((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	j = i;
	while (--j >= 0)
	{
		s[j] = (n % 10) + '0';
		n /= 10;
	}
	s[i] = '\0';
	return (s);
}
