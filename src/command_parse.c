/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 20:56:08 by gleger            #+#    #+#             */
/*   Updated: 2014/05/18 16:10:58 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void			ft_open_close(void)
{
	static int	fd;

	if (fd)
	{
		close(fd);
		fd = 0;
		return ;
	}
	fd = open("/tmp/sh.backquote", O_RDWR | O_TRUNC | O_CREAT, 0666);
	ft_dup2(fd, 1);
}

static int		ft_parse_backquote(t_cmd *cmd)
{
	int	index;
	int	start;
	int	count;

	index = 0;
	start = 0;
	while (cmd->split[index])
	{
		start = 0;
		count = 0;
		while (cmd->split[index][count])
		{
			if (cmd->split[index][count] == '`')
			{
				if (start == 0)
					start = 1;
				else
					start = 0;
			}
			count++;
		}
		index++;
	}
	return (start);
}

static int		ft_backquote(t_cmd *cmd, t_env *env, t_dir *dir)
{
	if (ft_parse_backquote(cmd))
		return (1);
	execute_backquote(cmd, env, dir);
	if (!cmd->split)
		return (-1);
	return (0);
}

int				command_parse(t_cmd *cmd, t_env *env, t_dir *dir)
{
	int	index;
	int	count;

	index = 0;
	if (cmd->split)
		array2d_free(cmd->split);
	cmd->split = ft_strsplit_all(cmd->raw);
	if (!(cmd->split[0]))
		return (0);
	ft_get_var(cmd, env);
	ft_globing(cmd);
	while (cmd->split[index])
	{
		count = 0;
		while (cmd->split[index][count])
		{
			if (cmd->split[index][count] < 0)
				cmd->split[index][count] = -1 * cmd->split[index][count];
			count++;
		}
		index++;
	}
	return (ft_backquote(cmd, env, dir));
}
