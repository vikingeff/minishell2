/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 13:41:19 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 13:23:52 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	sh_cmd(void)
{
	pid_t	pid_trol;
	char	**table;

	if ((pid_trol = fork()) == 0)
	{
		table = ft_strsplit("cat MAN/cmd", ' ');
		execve("/bin/cat", table, NULL);
	}
	else
		wait(NULL);
}

int		sh_echo(t_cmd *cmd)
{
	int	index;
	int	opt;

	opt = 0;
	if (cmd->split[1] && ft_strcmp(cmd->split[1], "-n") == 0)
		opt = 1;
	index = 1 + opt;
	while (cmd->split[index])
	{
		ft_putstr(cmd->split[index]);
		if (cmd->split[index + 1])
			ft_putstr(" ");
		index++;
	}
	if (!opt)
		ft_putstr("\n");
	return (0);
}

void	sh_exit(t_cmd *cmd)
{
	cmd->exit = 1;
	ft_putendl_fd("\033[1;34mMinishell : exit\033[m", 2);
}
