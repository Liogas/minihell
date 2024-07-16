/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:04:38 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:31:34 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	int		size_little;

	if (little[0] == '\0' || !little || little == big)
		return ((char *)big);
	if (n > 0)
	{
		size_little = ft_strlen((char *)little);
		i = 0;
		while (i < n && big[i] != '\0')
		{
			if (big[i] == little[0])
			{
				if (!ft_strncmp(big + i, little, size_little)
					&& i + size_little <= n)
					return ((char *)big + i);
			}
			i++;
		}
	}
	return (NULL);
}
