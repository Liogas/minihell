/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:04:04 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:30:21 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	il;

	if (!dst && size <= 0)
		return (0);
	il = ft_strlen(dst);
	if (il >= size)
		il = size;
	if (il < size - 1 && size > 0)
	{
		i = 0;
		while (i + il < size - 1 && src[i] != '\0')
		{
			dst[i + il] = src[i];
			i++;
		}
		dst[i + il] = '\0';
	}
	return (il + ft_strlen((char *)src));
}
