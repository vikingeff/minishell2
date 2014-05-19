/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 17:53:36 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:13:51 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int		sh_setenv_var(t_var *p_var, t_cmd *cmd, t_env *env)
{
	free(p_var->value);
	p_var->value = (cmd->split[2]) ? ft_strdup(cmd->split[2]) : NULL;
	if (cmd->env)
		array2d_free(cmd->env);
	cmd->env = env_list_to_array(env->var, env->nb);
	return (0);
}

static int		setenv_isvalid(t_cmd *cmd, t_env *env)
{
	int			i;

	i = -1;
	if (!cmd->split[1])
	{
		sh_env(cmd, env, NULL);
		return (1);
	}
	while (cmd->split[1][++i])
		if (cmd->split[1][i] == '=')
			return (error(2, NULL));
	return (0);
}

static t_var	*init_strings(t_var *src, t_var **p_var)
{
	*p_var = src;
	return (*p_var);
}

int				sh_setenv(t_cmd *cmd, t_env *env)
{
	t_var		*temp;
	t_var		*start;
	t_var		*p_var;

	start = NULL;
	if (setenv_isvalid(cmd, env))
		return (1);
	temp = init_strings(env->var, &p_var);
	while (p_var)
	{
		if (ft_strcmp(cmd->split[1], p_var->name) == 0)
			return (sh_setenv_var(p_var, cmd, env));
		temp = p_var;
		p_var = p_var->next;
	}
	env_list_add(&temp, &start);
	temp->name = ft_strdup(cmd->split[1]);
	temp->value = (cmd->split[2]) ? ft_strdup(cmd->split[2]) : NULL;
	env->nb++;
	if (cmd->env)
		array2d_free(cmd->env);
	if (env->var == NULL)
		env->var = temp;
	cmd->env = env_list_to_array(env->var, env->nb);
	return (0);
}
