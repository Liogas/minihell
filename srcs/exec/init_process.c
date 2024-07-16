/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:11:55 by glions            #+#    #+#             */
/*   Updated: 2024/07/16 11:30:54 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_pipe_out(t_process **new_p, t_dt_elem *token)
{
	token = token->next;
	if (token && token->type == PIPE_LINE)
	{
		(*new_p)->pipe_out = malloc(sizeof(int) * 2);
		if (!(*new_p)->pipe_out)
			return (0);
		if (pipe((*new_p)->pipe_out) == -1)
		{
			free((*new_p)->pipe_out);
			(*new_p)->pipe_out = NULL;
			return (0);
		}
		// printf("test->%d;%d\n", (*new_p)->pipe_out[0], (*new_p)->pipe_out[1]);
		// printf("pipe_out mis à jour\n");
	}
	return (1);
}

static int	init_pipe_in(t_process **new_p, t_process *curr_p)
{
	t_list_gl	*el;

	if (curr_p->utils.new_p)
	{
		(*new_p)->pipe_in = malloc(sizeof(int) * 2);
		if (!(*new_p)->pipe_in || pipe((*new_p)->pipe_in) == -1)
			return (0);
		(*new_p)->utils.close_in = 1;
		close((*new_p)->pipe_in[1]);
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
	printf("PIPE IN RECUP\n");
	if (curr_p->utils.last == 0)
	{
		// printf("Il vient d'une commande\n");
		// print_cmd((t_cmd *)el->content);
		// printf("%d,%d\n", ((t_cmd *)el->content)->pipe_out[0], ((t_cmd *)el->content)->pipe_out[1]);
		(*new_p)->pipe_in = ((t_cmd *)el->content)->pipe_out;
	}
	else
	{
		// printf("Il vient d'un processus\n");
		// printf("%d,%d\n", ((t_process *)el->content)->pipe_out[0], ((t_process *)el->content)->pipe_out[1]);
		(*new_p)->pipe_in = ((t_process *)el->content)->pipe_out;
	}
	return (1);
}

static int	init_pipes(t_process **new_p, t_process *curr_p, t_dt_elem *tokens)
{
	// printf("Je rentre ici\n");
	if (!init_pipe_in(new_p, curr_p))
		return (0);
	if (!init_pipe_out(new_p, tokens))
		return (0);
	return (1);
}

int	init_process(t_dt_elem *tokens, t_process *curr_p, t_minish *minish,
		t_process **new_p)
{
	*new_p = create_process(minish->check->bltn, curr_p->env, curr_p);
	if (!*new_p)
		return (free_process(new_p, 0), 0);
	if (!init_pipes(new_p, curr_p, tokens))
		return (free_process(new_p, 0), 0);
	curr_p->utils.last = 1;
	if (!addback_list_gl(&curr_p->childs, new_element_gl(*new_p)))
		return (free_process(new_p, 0), 0);
	// printf("Mon nouveau process : \n");
	// print_process(*new_p, 0);
	return (1);
}