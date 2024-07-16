/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:04:53 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:30:40 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	m;

	i = 0;
	m = -1;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			m = i;
		i++;
	}
	if (c == 0)
		return ((char *)s + i);
	if (m == -1)
		return (NULL);
	return ((char *)s + m);
}
