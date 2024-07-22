#include "minishell.h"

char	*search_path_built(t_cmd *curr, char *exec, t_minish *dt)
{
	int i;

	if (ft_strcmp(curr->tab_opt[0], "echo") == 0)
	{
		exec = "ft_echo";
		return (exec);
	}
	else if (ft_strcmp(curr->tab_opt[0], "pwd") == 0)
	{
		ft_pwd();
		(free_cmd(curr), free_minish(dt), exit(EXIT_SUCCESS));
	}
	else if (ft_strcmp(curr->tab_opt[0], "cd") == 0)
	{
		i = 0;
		while (curr->tab_opt && curr->tab_opt[i])
		{
			if (ft_strcmp(curr->tab_opt[i], "cd") == 0)
			{
				if (!change_dir(curr, dt, i, 0))
					return (0);
				(free_cmd(curr), free_minish(dt), exit(EXIT_SUCCESS));
			}
			i++;
		}
	}	
	else if (!other_built(curr, dt))
		return (NULL);
	return (NULL);
}

char	*search_path_cmd(t_cmd *cmd, t_minish *dt)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (dt->check->paths && dt->check->paths[i])
	{
		tmp = ft_strjoin(dt->check->paths[i], "/");
		if (!tmp)
			return (NULL);
		tmp = ft_strjoin_w_free(tmp, cmd->tab_opt[0]);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK | X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

char	*exec_builtin(t_cmd *cmd, t_minish *dt)
{
	char	*tmp;
	char	*exec_name;

	exec_name = NULL;
	tmp = NULL;
	exec_name = search_path_built(cmd, exec_name, dt);
	if (!exec_name)
		return (NULL);
	tmp = ft_strjoin(getcwd(tmp, 80), "/");
	if (!tmp)
		return (NULL);
	tmp = ft_strjoin_w_free(tmp, exec_name);
	if (!tmp)
		return (NULL);
	if (access(tmp, F_OK | X_OK) == 0)
		return (tmp);
	return (free(tmp), NULL);
}

int	check_if_builtin(char **bltn, t_cmd *curr)
{
	int	i;
	int	j;

	i = 0;
	while (bltn && bltn[i])
	{
		j = 0;
		while (curr->tab_opt && curr->tab_opt[j])
		{
			if (ft_strcmp(curr->tab_opt[j], bltn[i]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

char	*get_path(t_cmd *cmd, t_minish *dt)
{
	char	*path_built;

	path_built = NULL;
	if (check_if_builtin(dt->check->bltn, cmd))
	{
		path_built = exec_builtin(cmd, dt);
		if (!path_built)
			return (NULL);
		return (path_built);
	}
	else
	{
		path_built = search_path_cmd(cmd, dt);
		if (!path_built)
			return (NULL);
		return (path_built);
	}
	return (printf("%s: command not found\n", cmd->tab_opt[0]), NULL);
}