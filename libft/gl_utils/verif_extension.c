/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:52:05 by glions            #+#    #+#             */
/*   Updated: 2024/04/11 12:18:45 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_utils.h"

int	verif_extension(char *path, char *ext)
{
	int	i;
	int	j;

	if (!path || !ext || !path[0] || !ext[0])
		return (0);
	i = ft_strlen(path) - 1;
	j = 1;
	while (path[i] && ext[ft_strlen(ext) - j])
		if (path[i++] != ext[ft_strlen(ext) - j++])
			return (0);
	return (1);
}
