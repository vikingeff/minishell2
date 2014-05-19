/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_ini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 16:04:28 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:13:49 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void			*ft_remember(t_cmd *cmd, t_dir *dir, t_env *env, int flag)
{
	static t_cmd	*c_cmd = NULL;
	static t_dir	*c_dir = NULL;
	static t_env	*c_env = NULL;

	if (flag == 0)
	{
		c_cmd = cmd;
		c_dir = dir;
		c_env = env;
	}
	if (flag == 1)
		return (c_cmd);
	if (flag == 2)
		return (c_dir);
	if (flag == 3)
		return (c_env);
	return (NULL);
}

static void		command_ini(t_cmd *cmd)
{
	cmd->exit = 0;
	cmd->split = NULL;
	cmd->env = NULL;
	cmd->raw = NULL;
	cmd->alias = NULL;
	cmd->ret = 0;
	cmd->hist = NULL;
	cmd->nav = NULL;
	cmd->save_cur = NULL;
	cmd->comp = -1;
	cmd->actual = NULL;
	cmd->s_cursor = -1;
	cmd->sig = 0;
}

int				shell_ini(t_cmd *cmd, t_dir *dir, t_env *env, char **environ)
{
	char	buff[2048];

	env->raw = environ;
	env->var = env_array_to_list(env);
	env->term = (t_term *)malloc(sizeof(t_term));
	command_ini(cmd);
	ft_remember(cmd, dir, env, 0);
	if (term_ini(env))
		return (-1);
	if (!(cmd->paths = ft_strsplit(env_get_value("PATH", env), ':')))
		return (-1);
	if (!(dir->pwd = ft_strdup(getcwd(buff, 2048)))
		|| !(dir->oldpwd = ft_strdup(env_get_value("OLDPWD", env)))
		|| !(dir->home = ft_strdup(env_get_value("HOME", env)))
		|| !(dir->user = ft_strdup(env_get_value("USER", env))))
		return (-1);
	return (0);
}
