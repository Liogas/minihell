/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:29:48 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:32:22 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

static unsigned int	ft_utoa_len(unsigned int n)
{
	unsigned int	i;
	unsigned int	m;

	i = 1;
	m = 1;
	while (n / m >= 10)
	{
		m *= 10;
		i++;
	}
	return (i);
}

static char	*ft_utoa_max(void)
{
	char	*s;
	char	*s_cpy;

	s = malloc(11 * sizeof(char));
	if (!s)
		return (NULL);
	s_cpy = "4294967295";
	ft_strlcpy(s, s_cpy, 11);
	return (s);
}

char	*ft_utoa(unsigned int n)
{
	char	*s;
	int		i;
	int		j;

	if (n == 4294967295)
		return (ft_utoa_max());
	i = ft_utoa_len(n);
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
