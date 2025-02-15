/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:29:30 by glions            #+#    #+#             */
/*   Updated: 2024/07/22 17:31:56 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_white(char c)
{
	return ((c >= 9 && c <= 13) || c == 32 || c == '\n');
}

int	accept_char(char c)
{
	return (c == '<' || c == '>' || c == '\"' || c == '\'' || c == '$'
		|| ft_isalnum(c) || is_white(c));
}

int	is_redir(char *str)
{
	return (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, "<", 1)
		|| !ft_strncmp(str, ">>", 2) || !ft_strncmp(str, ">", 1));
}
