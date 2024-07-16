/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:40:31 by glions            #+#    #+#             */
/*   Updated: 2024/07/16 13:07:09 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_dup(t_process *curr_p)
{
	if (curr_p->pipe_in)
	{
		printf("L'entrée du process[%d] devient : %d\n", getpid(), curr_p->pipe_in[0]);
		if (dup2(curr_p->pipe_in[0], STDIN_FILENO) == -1)
			return (0);
		close(curr_p->pipe_in[0]);
	}
	if (curr_p->pipe_out)
	{
		printf("La sortie du process[%d] devient : %d\n", getpid(), curr_p->pipe_out[1]);
		if (dup2(curr_p->pipe_out[1], STDOUT_FILENO) == -1)
			return (0);
		close(curr_p->pipe_out[1]);
	}
	return (1);
}

static void	do_operator(t_dt_elem **tokens, t_process *curr_p, t_process **p, t_cmd **c)
{
	if ((*tokens)->type == PIPE_LINE)
		*tokens = (*tokens)->next;
	else if ((*tokens)->type == AND)
	{
		wait_all_pid(curr_p);
		while (curr_p->status > 0 && *tokens && (*tokens)->type != PIPE_LINE
			&& (*tokens)->type != OR)
			*tokens = (*tokens)->next;
		curr_p->utils.last = -1;
	}
	else if ((*tokens)->type == OR)
	{
		wait_all_pid(curr_p);
		while (curr_p->status == 0 && *tokens && (*tokens)->type != PIPE_LINE
			&& (*tokens)->type != AND)
			*tokens = (*tokens)->next;
		curr_p->utils.last = -1;
	}
	if (*tokens && (*tokens)->type == PIPE_LINE)
		curr_p->utils.new_p = 1;
	if (*tokens && type_is_operator((*tokens)->type))
		*tokens = (*tokens)->next;
	*c = NULL;
	*p = NULL;
}

static int	exec_process(t_dt_elem *tokens, t_process *curr_p, t_minish *minish)
{
	t_cmd		*cmd;
	t_process	*process;

	while (tokens)
	{
		// printf("process[%d] : Je travaille avec le token->%s;%d\n", getpid(), tokens->value, tokens->type);
		if (tokens->type == BLOCK)
		{

			// printf("process[%d] : Je vais créer un nouvel enfant\n", getpid());
			if (!init_process(tokens, curr_p, minish, &process))
				return (0);
			if (!start_process(tokens->content, process, minish, 1))
				return (0);
			// printf("PID DE l'enfant->%d\n", process->pid);
			print_process(process, 0);
			tokens = tokens->next;
			if (tokens && tokens->type == PIPE_LINE)
				tokens = tokens->next;
		}
		else if (!type_is_operator(tokens->type))
		{
			// printf("process[%d] : Je vais créer une nouvelle commande\n", getpid());
			if (!init_cmd(&tokens, curr_p, minish, &cmd))
				return (0);
			if (!exec_cmd(cmd, curr_p, minish))
				return (0);
			// printf("PID DE la commande->%d\n", cmd->pid);
			// print_cmd(cmd);
			if (tokens && tokens->type == PIPE_LINE)
				tokens = tokens->next;
		}
		else
			do_operator(&tokens, curr_p, &process, &cmd);
	}
	return (1);
}

int	start_process(t_dt_elem *tokens, t_process *curr_p, t_minish *minish,
		int mode)
{
	int	status;

	if (mode)
	{
		curr_p->pid = fork();
		if (curr_p->pid == -1)
			return (0);
		else if (curr_p->pid == 0)
		{
			if (!check_dup(curr_p))
				(close_process(curr_p, minish, 1, 1), free_process(&curr_p, 1), free_minish(minish),
					exit(EXIT_FAILURE));
			if (!exec_process(tokens, curr_p, minish))
				(close_process(curr_p, minish, 1, 1), free_process(&curr_p, 1), free_minish(minish),
					exit(EXIT_FAILURE));
			close_process(curr_p, minish, 1, 0);
			wait_all_pid(curr_p);
			status = curr_p->status;
			(free_process(&curr_p, 1), free_minish(minish));
			exit(status);
		}
		return (1);
	}
	else if (!exec_process(tokens, curr_p, minish))
		return (0);
	return (1);
}
