/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 20:53:59 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 14:15:18 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			command_shell_next(t_cmd *cmd, t_env *env, t_dir *dir, int *ret)
{
	int		modify;

	modify = 1;
	if (ft_strcmp(cmd->split[0], "cd") == 0)
		*ret = sh_cd(cmd, env, dir);
	else if (ft_strcmp(cmd->split[0], "echo") == 0)
		*ret = sh_echo(cmd);
	else if (ft_strcmp(cmd->split[0], "pr0n") == 0)
		sh_cmd();
	else if (ft_strcmp(cmd->split[0], "alias") == 0)
		*ret = sh_alias(cmd);
	else if (ft_strcmp(cmd->split[0], "unalias") == 0)
		*ret = sh_unalias(cmd);
	else if (ft_strcmp(cmd->split[0], "history") == 0)
		*ret = print_hist(cmd);
	else
		modify = 0;
	return (modify);
}

int			command_shell(t_cmd *cmd, t_env *env, t_dir *dir)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd->split[0], "exit") == 0)
		sh_exit(cmd);
	else if (cmd->split[0][0] == '!' && cmd->split[0][1])
		ret = hist_chr(cmd, dir, env);
	else if (ft_strcmp(cmd->split[0], "env") == 0)
		ret = sh_env(cmd, env, dir);
	else if (ft_strcmp(cmd->split[0], "unsetenv") == 0
		|| ft_strcmp(cmd->split[0], "unset") == 0)
		ret = sh_unsetenv(cmd, env);
	else if (ft_strcmp(cmd->split[0], "setenv") == 0
		|| ft_strcmp(cmd->split[0], "export") == 0)
		ret = sh_setenv(cmd, env);
	else if (command_shell_next(cmd, env, dir, &ret))
		;
	else
		return (-1);
	cmd->ret = ret;
	return (ret);
}
