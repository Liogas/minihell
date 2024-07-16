/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:26:46 by glions            #+#    #+#             */
/*   Updated: 2024/06/04 10:48:49 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(const char *path)
{
	if (chdir(path) == -1)
		return (perror("minish: "), errno);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	printf("Au depart je suis dans le dossier -> %s\n", getcwd(NULL, 0));
// 	if (ft_cd("../.."))
// 		return (errno);
// 	printf("apres je suis dans le dossier -> %s\n", getcwd(NULL, 0));
// 	return (0);
// }