/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_get_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 21:16:23 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:14:24 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		command_get_env(t_cmd *cmd, t_env *env, t_dir *dir)
{
	if (cmd->env)
		array2d_free(cmd->env);
	if (!(cmd->env = env_list_to_array(env->var, env->nb)))
		return (-1);
	if (cmd->paths)
		array2d_free(cmd->paths);
	cmd->paths = ft_strsplit(env_get_value("PATH", env), ':');
	if (env_get_value("HOME", env))
	{
		if (dir->home)
			free(dir->home);
		dir->home = ft_strdup(env_get_value("HOME", env));
	}
	if (env_get_value("USER", env))
	{
		if (dir->user)
			free(dir->user);
		dir->user = ft_strdup(env_get_value("USER", env));
	}
	return (0);
}
