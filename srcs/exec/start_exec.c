/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:51:29 by glions            #+#    #+#             */
/*   Updated: 2024/07/16 15:04:34 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_exec(t_minish *dt_minish)
{
	t_process	*main_process;

	main_process = create_process(dt_minish->check->bltn, dt_minish->env_minish,
			NULL);
	if (!main_process)
		return (0);
	if (!start_process(dt_minish->block_token, main_process, dt_minish, 0))
		return (close_process(main_process, dt_minish, 0, 1),
			free_process(&main_process, 0), 0);
	close_process(main_process, dt_minish, 0, 1);
	wait_all_pid(main_process);
	free_process(&main_process, 0);
	return (1);
}
