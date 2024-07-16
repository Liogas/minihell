/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:03:36 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:29:44 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (n > 0 && (dest || src))
	{
		if (dest > src)
		{
			while (n > 0)
			{
				*((char *)dest + n - 1) = *((char *)src + n - 1);
				n--;
			}
		}
		else
		{
			i = 0;
			while (i < n)
			{
				*((char *)dest + i) = *((char *)src + i);
				i++;
			}
		}
	}
	return (dest);
}
