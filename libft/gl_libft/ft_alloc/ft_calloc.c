/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:53:32 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:35:16 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*memz;

	if (((long long)elementCount < 0 && (long long)elementSize < 0)
		|| ((long long)elementCount < 0 && elementSize != 0)
		|| (elementCount != 0 && (long long)elementSize < 0)
		|| ((long long)elementCount > 0xffffffff
			|| (long long)elementSize > 0xffffffff))
		return (NULL);
	memz = malloc(elementCount * elementSize);
	if (!memz)
		return (NULL);
	ft_bzero(memz, elementCount * elementSize);
	return (memz);
}
