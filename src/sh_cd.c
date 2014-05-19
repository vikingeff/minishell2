/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/04 18:04:13 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 13:06:02 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int		change_dir(char *n_dir, t_dir *dir, t_cmd *cmd, t_env *env)
{
	char	buff[2000];

	if (chdir(n_dir) == -1)
	{
		perror("cd");
		return (255);
	}
	array2d_free(cmd->split);
	cmd->split = ft_strsplit_all("setenv OLDPWD random");
	free(cmd->split[2]);
	cmd->split[2] = ft_strdup(dir->pwd);
	free(dir->oldpwd);
	dir->oldpwd = ft_strdup(dir->pwd);
	sh_setenv(cmd, env);
	array2d_free(cmd->split);
	cmd->split = ft_strsplit_all("setenv PWD random");
	free(cmd->split[2]);
	cmd->split[2] = ft_strdup(getcwd(buff, 2000));
	free(dir->pwd);
	dir->pwd = ft_strdup(getcwd(buff, 2000));
	sh_setenv(cmd, env);
	return (0);
}

static int		sh_cd_home(t_cmd *cmd, t_env *env, t_dir *dir)
{
	int	ret;

	ret = 0;
	if (access(dir->home, F_OK) == 0)
		ret = change_dir(dir->home, dir, cmd, env);
	else
	{
		error(33, dir->home);
		return (256);
	}
	return (ret);
}

static int		sh_cd_oldpwd(t_cmd *cmd, t_env *env, t_dir *dir)
{
	char	*str;
	int		ret;

	ret = 0;
	if (access(dir->oldpwd, F_OK) == 0)
	{
		str = ft_strdup(dir->oldpwd);
		ret = change_dir(str, dir, cmd, env);
		ft_putendl(str);
		free(str);
	}
	else
	{
		error(33, dir->oldpwd);
		return (256);
	}
	return (ret);
}

int				sh_cd(t_cmd *cmd, t_env *env, t_dir *dir)
{
	int			ret;

	ret = 0;
	if (!cmd->split[1] || cmd->split[1][0] == '~')
		return (sh_cd_home(cmd, env, dir));
	else if (cmd->split[1][0] == '-')
		return (sh_cd_oldpwd(cmd, env, dir));
	ret = change_dir(cmd->split[1], dir, cmd, env);
	return (ret);
}
