/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:51:47 by glions            #+#    #+#             */
/*   Updated: 2024/07/19 15:56:58 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_redir(t_cmd **cmd, t_dt_elem **redir, t_dt_elem *file)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->type = (*redir)->type;
	new->name_file = ft_strdup(file->value);
	if (!new->name_file)
		return (free(new), 0);
	new->next = NULL;
	new->name_heredoc = NULL;
	new->fd_heredoc = -1;
	tmp = (*cmd)->list_redirc;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		(*cmd)->list_redirc = new;
	else
		tmp->next = new;
	*redir = (*redir)->next;
	return (1);
}

static char	*ft_getenv(char *name, t_list_gl *env)
{
	while (env)
	{
		if (!ft_strcmp(name, ((t_node_env *)env->content)->name))
			return (ft_strdup(((t_node_env *)env->content)->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

static int	add_dollar(char **value, int *i, t_dt_elem *token,
		t_minish *dt_minish)
{
	int		j;
	char	*tmp;
	char	*res;

	tmp = NULL;
	if (token->value[*i + 1] == '?')
	{
		tmp = ft_itoa(dt_minish->status);
		if (!tmp)
			return (free(*value), 0);
		*value = ft_strjoin_w_free(*value, tmp);
		if (!*value)
			return (free(*value), free(tmp), 0);
		free(tmp);
		*i += 2;
		return (1);
	}
	j = 0;
	(*i)++;
	while (token->value[*i + j] && (isalnum(token->value[*i + j]) || token->value[*i + j] == '_'))
		j++;
	tmp = ft_strndup(token->value + *i, j - *i + 1);
	if (!tmp)
		return (free(*value), 0);
	res = ft_getenv(tmp, dt_minish->env_minish);
	if (!res)
		return (free(*value), free(tmp), 0);
	*value = ft_strjoin_w_free(*value, res);
	if (!value)
		return (free(tmp), free(res), 0);
	*i += j;
	return (1);
}

static int	add_normal(char **value, int *i, t_dt_elem *token)
{
	int		j;
	char	*tmp;

	printf("value->%s\n", *value);
	printf("i->%d\n", *i);
	j = 0;
	while (token->value[*i + j] && (token->state == IN_QUOTE || (token->value[*i + j] != '$' || !(token->value[*i + j + 1] && (isalpha(token->value[*i + j + 1]) || token->value[*i + j + 1] == '?')))))
		j++;
	tmp = ft_strndup(token->value + *i, j);
	if (!tmp)
		return (free(*value), 0);
	*i += j;
	if (!*value)
	{
		*value = tmp;
		return (1);
	}
	*value = ft_strjoin_w_free(*value, tmp);
	if (!*value)
		return (free(tmp), 0);
	free(tmp);
	return (1);
}

static char	*get_value(t_dt_elem *token, t_minish *dt_minish)
{
	int		i;
	char	*value;

	i = 0;
	value = malloc(sizeof(char *));
	value[0] = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$' && token->state != IN_QUOTE && token->value[i
			+ 1] && (isalpha(token->value[i + 1]) || token->value[i
				+ 1] == '?'))
		{
			if (!add_dollar(&value, &i, token, dt_minish))
				return (NULL);
		}
		else if (!add_normal(&value, &i, token))
			return (NULL);
	}
	return (value);
}

static int	add_opt(t_cmd **cmd, t_dt_elem *token, t_minish *dt_minish)
{
	static char	*tmp;
	char		*value;

	if (!token)
	{
		(*cmd)->tab_opt = ft_split(tmp, '\n');
		if (!(*cmd)->tab_opt)
			return (0);
		free(tmp);
		tmp = NULL;
		return (1);
	}
	value = get_value(token, dt_minish);
	if (!value)
		return (0);
	else if (!tmp)
		tmp = ft_strdup(value);
	else
	{
		tmp = ft_strjoin_w_free(tmp, "\n");
		if (!tmp)
			return (0);
		tmp = ft_strjoin_w_free(tmp, value);
		free(value);
	}
	if (!tmp)
		return (0);
	return (1);
}

static int	add_opt_redir(t_dt_elem **start, t_cmd **new_c, t_minish *dt_minish)
{
	while (*start && !type_is_operator((*start)->type))
	{
		if (!add_opt(new_c, *start, dt_minish))
			return (0);
		else if (type_is_redir((*start)->type))
			if (!add_redir(new_c, start, (*start)->next))
				return (0);
		*start = (*start)->next;
	}
	if (!add_opt(new_c, NULL, dt_minish))
		return (0);
	return (1);
}

static void	init_utils(t_cmd *cmd)
{
	cmd->utils.n_cmd = 0;
	cmd->utils.n_pipe = 0;
}

t_cmd	*create_cmd(t_dt_elem **start, t_minish *dt_minish)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->status = 0;
	cmd->id = -1;
	cmd->pid = -1;
	cmd->list_redirc = NULL;
	cmd->tab_opt = NULL;
	cmd->tab_pipes = NULL;
	cmd->next = NULL;
	cmd->tab_fd = NULL;
	if (!add_opt_redir(start, &cmd, dt_minish))
		return (free_cmd(cmd), NULL);
	cmd->pos_cmd = 0;
	init_utils(cmd);
	return (cmd);
}
