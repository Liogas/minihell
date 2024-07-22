/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:25:01 by glions            #+#    #+#             */
/*   Updated: 2024/07/22 18:52:45 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_whitespace(char *str, t_dt_elem **token, t_check *check, int j)
{
	enum e_type	type;

	if (check->curr_state == IN_DQUOTE || check->curr_state == IN_QUOTE)
		type = WORD;
	else
		type = WHITE_SPACE;
	*token = create_dt_elem(ft_strndup(str + j, 1), type, check->curr_state);
	if (!*token)
		return (0);
	return (1);
}

static int	pars_env(char **value, char *str, t_minish *dt_minish, int *pos)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	printf("Taille de la variable->%d\n", i - 1);
	tmp = ft_strndup(str + 1, i - 1);
	if (!tmp)
		return (0);
	printf("Variable->%s\n", tmp);
	tmp2 = ft_getenv(tmp, dt_minish->env_minish);
	if (!tmp2)
		return (free(tmp), 0);
	printf("Valeur de la variable dans l'env->%s\n", tmp2);
	free(tmp);
	if (*value)
	{
		*value = ft_strjoin_w_free(*value, tmp2);
		free(tmp2);
		if (!*value)
			return (0);
	}
	else
		*value = tmp2;
	printf("Ma value contient mtn->%s\n", *value);
	*pos += i;
	printf("Ma pos devient donc->%d, je suis au C->%c\n", *pos, str[*pos]);
	return (1);
}

static int	pars_status(char **value, t_minish *data_minish,
		int *pos)
{
	char	*tmp;

	tmp = ft_itoa(data_minish->status);
	if (!tmp)
		return (0);
	if (*value)
	{
		*value = ft_strjoin_w_free(*value, tmp);
		free(tmp);
		if (!*value)
			return (0);
	}
	else
		*value = tmp;
	printf("Ma value contient mtn->%s\n", *value);
	*pos += 2;
	return (1);
}

static int	pars_normal(char **value, char *str, t_minish *dt_minish, int *pos)
{
	char	*tmp;
	int		i;

	printf("Entrée dans pars_normal\n");
	i = 0;
	while (str[i] && ((dt_minish->check->curr_state == GENERAL
				&& (!is_white(str[i]) && (str[i] != '$' || i == 0) && !is_redir(str + i) && str[i] != '|'))
			|| (dt_minish->check->curr_state == IN_DQUOTE && (str[i] != '$' || i == 0) && str[i] != '\"')
			|| (dt_minish->check->curr_state == IN_QUOTE && str[i] != '\'')))
		i++;
	printf("taille du texte recup->%d\n", i);
	tmp = ft_strndup(str, i);
	if (!tmp)
		return (printf("11111\n"), 0);
	printf("Valeur du texte->%s\n", tmp);
	if (*value)
	{
		*value = ft_strjoin_w_free(*value, tmp);
		free(tmp);
		if (!*value)
			return (printf("22222\n"), 0);
	}
	else
		*value = tmp;
	printf("Ma value contient mtn->%s\n", *value);
	*pos += i;
	printf("Ma pos devient donc->%d, je suis au C->%c\n", *pos, str[*pos]);
	return (1);
}

int	token_word(char *str, t_dt_elem **token, t_minish *dt_minish, int *j)
{
	char 	*value;
	int		i;

	value = NULL;
	i = 0;
	printf("Je démarre avec str->%s\n", str);
	while (str[i])
	{
		if (dt_minish->check->curr_state == GENERAL && (is_white(str[i]) || is_redir(str + i) || str[i] == '|' || str[i] == '\"' || str[i] == '\''))
			break ;
		else if (dt_minish->check->curr_state == IN_DQUOTE && str[i] == '\"')
			break ;
		else if (dt_minish->check->curr_state == IN_QUOTE && str[i] == '\'')
			break ;
		if ((dt_minish->check->curr_state == GENERAL || dt_minish->check->curr_state == IN_DQUOTE) && str[i] == '$' && str[i + 1] && (str[i + 1] && (isalpha(str[i + 1])
					|| str[i + 1] == '_')))
		{
			if (!pars_env(&value, str + i, dt_minish, &i))
				return (printf("oupsi\n"), 0);
		}
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		{
			if (!pars_status(&value, dt_minish, &i))
				return (printf("oupso\n"), 0);
		}
		else if (!pars_normal(&value, str + i, dt_minish, &i))
			return (printf("oupsa\n"), 0);
	}
	*token = create_dt_elem(value, WORD, dt_minish->check->curr_state);
	if (!*token)
		return (printf("oupso\n"), free(value), 0);
	*j += i - 1;
	printf("Je sors avec j->%d\n", *j);
	return (1);
}
