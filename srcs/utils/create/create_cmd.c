/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:51:47 by glions            #+#    #+#             */
/*   Updated: 2024/07/17 16:14:45 by glions           ###   ########.fr       */
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

static int	add_opt(t_cmd **cmd, t_dt_elem *token)
{
	static char	*tmp;

	if (!token)
	{
		(*cmd)->tab_opt = ft_split(tmp, '\n');
		if (!(*cmd)->tab_opt)
			return (0);
		free(tmp);
		tmp = NULL;
		return (1);
	}
	else if (!tmp)
		tmp = ft_strdup(token->value);
	else
	{
		tmp = ft_strjoin_w_free(tmp, "\n");
		if (!tmp)
			return (0);
		tmp = ft_strjoin_w_free(tmp, token->value);
	}
	if (!tmp)
		return (0);
	return (1);
}

static int	add_opt_redir(t_dt_elem	**start, t_cmd **new_c)
{
	while (*start && !type_is_operator((*start)->type))
	{
		if (!add_opt(new_c, *start))
			return (0);
		else if (type_is_redir((*start)->type))
			if (!add_redir(new_c, start, (*start)->next))
				return (0);
		*start = (*start)->next;
	}
	if (!add_opt(new_c, NULL))
		return (0);
	return (1);
}

static void	init_utils(t_cmd *cmd)
{
	cmd->utils.n_cmd = 0;
	cmd->utils.n_pipe = 0;
}

t_cmd   *create_cmd(t_dt_elem **start)
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
	if (!add_opt_redir(start, &cmd))
		return (free_cmd(cmd), NULL);
	cmd->tab_pipes = NULL;
	cmd->next = NULL;
	cmd->pos_cmd = 0;
	cmd->tab_fd = NULL;
	init_utils(cmd);
	return (cmd);
}
