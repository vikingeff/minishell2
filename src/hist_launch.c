/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 17:53:14 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:14:03 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			filling_checking(t_cmd *cmd)
{
	char		*tmp;

	tmp = ft_strsub(cmd->raw, 0, 7);
	if (cmd->raw && (cmd->raw[0] != '!') && (ft_strcmp(tmp, "history")))
	{
		free(tmp);
		return (1);
	}
	else
	{
		free(tmp);
		return (0);
	}
}

void		ft_lauch_history(t_cmd *cmd, t_dir *dir, t_env *env, char *newcmd)
{
	t_list		*arg;

	arg = NULL;
	free(cmd->raw);
	cmd->raw = ft_strdup(newcmd);
	ft_main_loop(cmd, dir, env, &arg);
	if (arg)
		ft_free_arg(&arg);
}
