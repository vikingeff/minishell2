/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 19:44:49 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:15:21 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

t_list		*ft_free_one(t_list *list)
{
	free(list->mot);
	free(list->valeure);
	if (list->next != NULL)
	{
		list = list->next;
		free(list->prev);
	}
	else
	{
		free(list);
		list = NULL;
	}
	return (list);
}

void		ft_free_arg(t_list **arg)
{
	while (*arg)
	{
		while ((*arg)->dir)
			(*arg)->dir = ft_free_one((*arg)->dir);
		*arg = ft_free_one(*arg);
	}
}

static void	ft_free_all(t_cmd *cmd, t_env *env, t_dir *dir)
{
	t_var	*tmp;

	if (cmd->split)
		array2d_free(cmd->split);
	array2d_free(cmd->env);
	array2d_free(cmd->paths);
	free(dir->pwd);
	free(dir->oldpwd);
	free(dir->home);
	free(dir->user);
	while (env->var)
	{
		tmp = env->var;
		env->var = env->var->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void		delete_temp_free(t_list **arg, t_cmd *cmd, t_env *env, t_dir *dir)
{
	if (access("/tmp/sh.heredoc", F_OK) == 0)
	{
		if (cmd->split)
			array2d_free(cmd->split);
		cmd->split = ft_strsplit("rm /tmp/sh.heredoc", ' ');
		command_execute(cmd, env, dir);
	}
	if (access("/tmp/sh.backquote", F_OK) == 0)
	{
		if (cmd->split)
			array2d_free(cmd->split);
		cmd->split = ft_strsplit("rm /tmp/sh.backquote", ' ');
		command_execute(cmd, env, dir);
	}
	ft_free_arg(arg);
	ft_free_all(cmd, env, dir);
}
