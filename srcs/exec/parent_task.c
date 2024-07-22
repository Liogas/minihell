#include "minishell.h"

t_list_gl	*copy_env_to_parent(int fd_env, t_list_gl **env)
{
	char	*line;
	char	*tmp;

	line = get_next_line(fd_env);
	if (!line)
		return (0);
	while (line)
	{
		tmp = ft_strndup(line, ft_strlen(line) - 1);
		if (!tmp)
			return (0);
		ft_export(tmp, env);
		free(tmp);
		line = get_next_line(fd_env);
	}
	return (*env);
}

int	parent_task(t_minish *dt)
{
	int	fd_env;

	if (dt->flag_env)
	{
		fd_env = open("a_supp", O_RDONLY);
		if (fd_env == -1)
			return (0);
		free_list_gl(&dt->env_minish, &free_node_env);
		dt->env_minish = NULL;
		dt->env_minish = copy_env_to_parent(fd_env, &dt->env_minish);
		if (!dt->env_minish)
			return (0);
		unlink("a_supp");
		close(fd_env);
	}
	return (1);
}