/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 12:02:54 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 13:11:27 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	ft_fd_tmp(char *str)
{
	char	*line;
	int		fd;

	fd = open("/tmp/sh.heredoc", O_RDWR | O_TRUNC | O_CREAT, 0666);
	ft_putstr("? ");
	signal(SIGINT, SIG_IGN);
	while (get_next_line(0, &line) && ft_strcmp(str, line))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		ft_putstr("? ");
	}
	close(fd);
	fd = open("/tmp/sh.heredoc", O_RDONLY);
	free(line);
	ft_signal();
	return (fd);
}

static int	ft_open(char *str, int select)
{
	int	fd;

	fd = 0;
	if (select == 1)
		fd = open(str, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else if (select == 0)
		fd = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (select == 2)
		fd = open(str, O_RDONLY);
	else if (select == 3)
		fd = ft_fd_tmp(str);
	if (fd == -1)
	{
		ft_putstr_fd("open error :", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	return (fd);
}

int			ft_get_fd(t_list *dir)
{
	int	fd;
	int	select;
	int	index;

	select = 0;
	if (dir == NULL)
		return (0);
	if (ft_strcmp(dir->mot, ">>") == 0)
		select = 1;
	else if (ft_strcmp(dir->mot, "<") == 0)
		select = 2;
	else if (ft_strcmp(dir->mot, "<<") == 0)
		select = 3;
	if (dir->valeure[0] < 0)
	{
		index = 0;
		while (dir->valeure[index])
		{
			dir->valeure[index] = -dir->valeure[index];
			index++;
		}
	}
	fd = ft_open(dir->valeure, select);
	return (fd);
}

t_list		*ft_close_arg(int fd[2], t_list *arg)
{
	ft_close(fd);
	return (arg);
}

int			ft_init_pipe(int pipenb, int *pipeval)
{
	*pipeval = pipenb;
	return (1);
}
