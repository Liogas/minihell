#include "minishell.h"

int	copy_env(t_list_gl *env, int fd)
{
	t_list_gl	*curr;
	t_node_env	*curr_env;

	curr = env;
	while (curr)
	{
		curr_env = curr->content;
		write(fd, curr_env->name, ft_strlen(curr_env->name));
		write(fd, "=", 1);
		write(fd, curr_env->value, ft_strlen(curr_env->value));
		write(fd, "\n", 1);
		curr = curr->next;
	}
	return (1);
}

int	exec_export(t_cmd *curr, t_minish *dt)
{
	int	fd_env;
	int	i;

	i = 1;
	fd_env = open("a_supp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_env == -1)
		return (0);
	while (curr->tab_opt && curr->tab_opt[i])
	{
		if (!ft_export(curr->tab_opt[i], &dt->env_minish))
			return (0);
		i++;
	}
	if (!copy_env(dt->env_minish, fd_env))
		return (0);
	close(fd_env);
	(free_cmd(curr), free_minish(dt), exit(EXIT_SUCCESS));
}

int	exec_unset(t_cmd *curr, t_minish *dt)
{
	int	fd_env;
	int	i;

	i = 1;
	fd_env = open("a_supp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_env == -1)
		return (0);
	while (curr->tab_opt && curr->tab_opt[i])
	{
		if (!ft_unset(&dt->env_minish, curr->tab_opt[i]))
			return (0);
		i++;
	}
	if (!copy_env(dt->env_minish, fd_env))
		return (0);
	close(fd_env);
	(free_cmd(curr), free_minish(dt), exit(EXIT_SUCCESS));
}

int	other_built(t_cmd *curr, t_minish *dt)
{
	if (ft_strcmp(curr->tab_opt[0], "env") == 0)
	{
		print_env(dt->env_minish);
		(free_cmd(curr), free_minish(dt), exit(EXIT_SUCCESS));
	}
	else if (ft_strcmp(curr->tab_opt[0], "export") == 0)
	{
		if (!exec_export(curr, dt))
			return (0);
	}
	else if (ft_strcmp(curr->tab_opt[0], "unset") == 0)
	{
		if (!exec_unset(curr, dt))
			return (0);
	}
	return (1);
}
