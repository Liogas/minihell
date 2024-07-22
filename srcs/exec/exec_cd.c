#include "minishell.h"

int	update_var(char **pwd, char **old_pwd)
{
	char	*tmp;
	char buff[100];
	int 	i;

	tmp = NULL;
	*pwd = ft_strjoin("PWD=", getcwd(buff, 100));
	if (!*pwd)
		return (0);
	*old_pwd = ft_strjoin("OLDPWD=", getcwd(buff, 100));
	if (!*old_pwd)
		return (0);
	i = ft_strlen(*old_pwd);
	while (i > 0 && (*old_pwd)[i] != '/')
		i--;
	tmp = ft_strndup(*old_pwd, i);
	free(*old_pwd);
	*old_pwd = ft_strdup(tmp);
	return (free(tmp), 1);
}

int	change_dir(t_cmd *cmd, t_minish *dt, int pos, int change)
{
	char	*pwd;
	char	*old_pwd;
	char	*tmp;
	char 	buff[150];

	pwd = NULL;
	old_pwd = NULL;
	tmp = ft_strjoin(getcwd(buff, 150), "/");
	if (!tmp)
		return (0);
	tmp = ft_strjoin_w_free(tmp, cmd->tab_opt[pos + 1]);
	if (!tmp)
		return (0);
	if (ft_cd(tmp) != 0)
		return (perror(""), 0);
	if (change == 1)
	{
		if (!update_var(&pwd, &old_pwd))
			return (0);
		if (!ft_export(pwd, &dt->env_minish))
			return (0);
		if (!ft_export(old_pwd, &dt->env_minish))
			return (0);
	}
	return (free(pwd), free(old_pwd), free(tmp), 1);
}
