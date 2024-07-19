/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:57:41 by glions            #+#    #+#             */
/*   Updated: 2024/07/19 11:55:05 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_libft.h"

char	*ft_strjoin_w_free(char *s1, char const *s2)
{
	char	*new_s;
	int		i;
	int		j;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return (free(s1), NULL);
	new_s = (char *)malloc((ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1) * sizeof(char));
	if (!new_s)
		return (free(s1), NULL);
	i = -1;
	j = -1;
	while (s1[++i] != '\0')
		new_s[++j] = s1[i];
	i = -1;
	while (s2[++i] != '\0')
		new_s[++j] = s2[i];
	new_s[++j] = '\0';
	free(s1);
	return (new_s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	new_s = (char *)malloc((ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
	{
		new_s[j] = s1[i];
		j++;
	}
	i = -1;
	while (s2[++i] != '\0')
	{
		new_s[j] = s2[i];
		j++;
	}
	new_s[j] = '\0';
	return (new_s);
}
