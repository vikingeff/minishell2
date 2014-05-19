/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 22:59:48 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 13:22:13 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

t_var			*env_lst_copy(t_env *env)
{
	t_var		*list;
	t_var		*start;
	t_var		*p_var;

	list = NULL;
	start = NULL;
	p_var = env->var;
	while (p_var)
	{
		if (env_list_add(&list, &start))
			return (NULL);
		list->name = ft_strdup(p_var->name);
		list->value = ft_strdup(p_var->value);
		p_var = p_var->next;
	}
	return (start);
}

static void		ft_modify_env(char *str, t_env *c_env)
{
	t_cmd	cmd;
	int		len;

	cmd.env = env_list_to_array(c_env->var, c_env->nb);
	len = ft_strlen(str) - (ft_strlen(ft_strchr(str, '=')));
	cmd.split = (char**)malloc(sizeof(char*) * 4);
	cmd.split[0] = ft_strdup("setenv");
	cmd.split[1] = ft_strsub(str, 0, len);
	cmd.split[2] = ft_strsub(str, len + 1, ft_strlen(str) - len - 1);
	cmd.split[3] = NULL;
	sh_setenv(&cmd, c_env);
	array2d_free(cmd.split);
	array2d_free(cmd.env);
}

static int		cmd_format(t_cmd *cmd, int *option)
{
	*option = 0;
	if (cmd->split[1] && cmd->split[1][0] == '-')
	{
		if (cmd->split[1][1] == 'i')
			*option = 1;
		else
			return (error(3, &cmd->split[1][1]));
	}
	return (0);
}

static int		ft_get_i(t_cmd *cmd, int i, t_env *c_env, t_cmd *c_cmd)
{
	while (cmd->split[i] && ft_strchr(cmd->split[i], '='))
		ft_modify_env(cmd->split[i++], c_env);
	c_cmd->env = env_list_to_array(c_env->var, c_env->nb);
	return (i);
}

int				sh_env(t_cmd *cmd, t_env *env, t_dir *dir)
{
	int			option;
	t_env		c_env;
	t_cmd		c_cmd;
	t_dir		c_dir;
	int			i;

	c_dir = *dir;
	if (cmd_format(cmd, &option))
		return (256);
	init_copy_env(&c_env, &c_cmd, &c_dir);
	if (option != 1)
	{
		c_env.var = env_lst_copy(env);
		c_env.nb = env->nb;
	}
	i = option + 1;
	i = ft_get_i(cmd, i, &c_env, &c_cmd);
	if (i < ft_tablen(cmd->split))
	{
		c_cmd.split = copy_table_i(cmd->split, i);
		command_execute(&c_cmd, &c_env, &c_dir);
		ft_free_c_env(&c_env, &c_cmd, &c_dir);
		return (0);
	}
	return (ft_put_env(&c_cmd, &c_env, &c_dir));
}
