/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:57:14 by glions            #+#    #+#             */
/*   Updated: 2024/04/24 20:31:47 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

static void	check_params(char const *s, unsigned int *start, size_t *len)
{
	size_t	s_len;

	s_len = ft_strlen((char *)s);
	if ((long long)*len - (long long)*start > (long long)s_len
		|| (long long)*len >= (long long)s_len - (long long)*start)
		*len = (long long)s_len - (long long)*start;
	if ((long long)*start > (long long)s_len || (long long)*len < 0)
	{
		*start = 0;
		*len = 0;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new_s;
	size_t		i;
	size_t		j;

	if (!s)
		return (NULL);
	check_params(s, &start, &len);
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
		{
			new_s[j] = s[i];
			j++;
		}
		i++;
	}
	new_s[j] = '\0';
	return (new_s);
}
