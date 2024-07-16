/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 03:12:22 by glions            #+#    #+#             */
/*   Updated: 2024/07/16 13:06:31 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_list_cmd(t_cmd *list, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
}

static int	init_pipe_out(t_cmd **new_c, t_dt_elem *token)
{
	if (token && token->type == PIPE_LINE)
	{
		(*new_c)->pipe_out = malloc(sizeof(int) * 2);
		if (!(*new_c)->pipe_out || pipe((*new_c)->pipe_out) == -1)
			return (0);
		// printf("Nouveau pipe_out[%d, %d]\n", (*new_c)->pipe_out[0], (*new_c)->pipe_out[1]);
	}
	return (1);
}

static int	init_pipe_in(t_cmd **new_c, t_process *curr_p)
{
	t_list_gl	*el;

	if (curr_p->utils.new_p)
	{
		(*new_c)->pipe_in = malloc(sizeof(int) * 2);
		if (!(*new_c)->pipe_in || (pipe((*new_c)->pipe_in) == -1))
			return (0);
		(*new_c)->utils.close_in = 1;
		close((*new_c)->pipe_in[1]);
		curr_p->utils.new_p = 0;
		return (1);
	}
	if (curr_p->utils.last == -1)
		return (1);
	el = curr_p->cmds;
	if (curr_p->utils.last == 1)
		el = curr_p->childs;
	while (el && el->next)
		el = el->next;
	if (curr_p->utils.last == 0)
		(*new_c)->pipe_in = ((t_cmd *)el->content)->pipe_out;
	else
		(*new_c)->pipe_in = ((t_process *)el->content)->pipe_out;
	return (1);
}

static int	check_next_token(t_dt_elem **tokens, t_cmd **new_c)
{
	t_cmd	*cmd;

	while (*tokens && (*tokens)->type == PIPE_LINE
		&& (*tokens)->next->type != BLOCK)
	{
		*tokens = (*tokens)->next;
		cmd = create_cmd(tokens);
		if (!cmd)
			return (0);
		add_list_cmd(*new_c, cmd);
	}
	return (1);
}

int	init_cmd(t_dt_elem **tokens, t_process *curr_p, t_minish *minish, t_cmd **new_c)
{
	(void)minish;
	*new_c = create_cmd(tokens);
	if (!*new_c)
		return (0);
	if (!check_next_token(tokens, new_c))
	{
		free_cmd(*new_c);
		new_c = NULL;
		return (0);
	}
	if (!init_pipe_out(new_c, *tokens) || !init_pipe_in(new_c, curr_p))
	{
		close_cmd(*new_c);
		free_cmd(*new_c);
		new_c = NULL;
		return (0);
	}
	curr_p->utils.last = 0;
	if (!addback_list_gl(&curr_p->cmds, new_element_gl(*new_c)))
	{
		close_cmd(*new_c);
		free_cmd(*new_c);
		new_c = NULL;
		return (0);
	}
	return (1);
}
