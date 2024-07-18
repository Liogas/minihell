/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:12:23 by glions            #+#    #+#             */
/*   Updated: 2024/07/18 15:42:26 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	start_minish(t_minish *dt)
{
	dt->check->line_cmd = readline("minihell 😈 > ");
	while (dt->check->line_cmd && ft_strcmp(dt->check->line_cmd, "exit") != 0)
	{
		add_history(dt->check->line_cmd);
		if (parsing(dt) == 0)
			ft_putstr_fd("Error syntax\n", 2);
		else
			if (start_exec(dt) == 0)
				return (free_minish(dt), printf("error start_exec\n"), 1);
		if (dt->block_token)
			free_dt_elem(&dt->block_token);
		dt->block_token = NULL;
		free(dt->check->line_cmd);
		dt->check->line_cmd = readline("minihell 😈 > ");
	}
	free_minish(dt);
	return (0);
}

// SIGABRT CTRL-\
// SIGINT CTRL-C

int	main(int ac, char **av, char **envp)
{
	t_minish			*dt_minish;

	(void)av;
	if (ac != 1)
		return (ft_putstr_fd("No args required\n", 2), 1);
	dt_minish = create_minish(envp);
	if (!dt_minish)
		return (1);
	return (start_minish(dt_minish));
}
