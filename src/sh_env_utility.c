/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 16:39:00 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:21:00 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void			ft_free_c_env(t_env *c_env, t_cmd *c_cmd, t_dir *dir)
{
	t_var	*tmp;

	tmp = NULL;
	array2d_free(c_cmd->env);
	array2d_free(c_cmd->paths);
	array2d_free(c_cmd->split);
	if (c_cmd->raw)
		free(c_cmd->raw);
	while (c_env->var)
	{
		tmp = c_env->var->next;
		free(c_env->var->name);
		free(c_env->var->value);
		free(c_env->var);
		c_env->var = tmp;
	}
	c_env->var = NULL;
	free(dir->home);
	free(dir->user);
}

int				ft_put_env(t_cmd *c_cmd, t_env *c_env, t_dir *dir)
{
	int	i;

	i = 0;
	while (c_cmd->env[i])
	{
		ft_putendl(c_cmd->env[i]);
		i++;
	}
	ft_free_c_env(c_env, c_cmd, dir);
	return (0);
}

void			init_copy_env(t_env *c_env, t_cmd *c_cmd, t_dir *c_dir)
{
	c_env->var = NULL;
	c_env->nb = 1;
	c_cmd->paths = NULL;
	c_dir->home = NULL;
	c_dir->user = NULL;
	c_dir->oldpwd = NULL;
	c_dir->pwd = NULL;
	c_cmd->raw = NULL;
	c_cmd->alias = NULL;
	c_cmd->split = NULL;
}
