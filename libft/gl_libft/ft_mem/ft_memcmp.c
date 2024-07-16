/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:03:20 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:30:00 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (n > 0 && (s1 || s2))
	{
		i = 0;
		while (i < n)
		{
			if (*((unsigned char *)s1 + i) != *((unsigned char *)s2 + i))
				return (*((unsigned char *)s1 + i)
					- *((unsigned char *)s2 + i));
			i++;
		}
	}
	return (0);
}
