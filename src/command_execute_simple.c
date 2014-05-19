/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute_simple.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 17:35:48 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:11:47 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	*ft_init_fd(t_list *arg)
{
	int			*fd;

	fd = (int *)malloc(sizeof(int) * 2);
	fd[0] = 0;
	fd[1] = 1;
	while (arg->dir)
	{
		if (ft_strcmp(arg->dir->mot, ">>") == 0
			|| ft_strcmp(arg->dir->mot, ">") == 0)
			fd[1] = ft_get_fd(arg->dir);
		if (ft_strcmp(arg->dir->mot, "<<") == 0
			|| ft_strcmp(arg->dir->mot, "<") == 0)
			fd[0] = ft_get_fd(arg->dir);
		arg->dir = arg->dir->next;
	}
	if (fd[0] == -1 || fd[1] == -1)
		return (NULL);
	ft_dup2(fd[0], 0);
	ft_dup2(fd[1], 1);
	return (fd);
}

static void	ft_reverse_fd(int *fd)
{
	ft_dup2(fd[0], 0);
	ft_dup2(fd[1], 1);
}

int			command_execute_simple(t_list *arg,
	t_cmd *cmd, t_env *env, t_dir *dir)
{
	int *fd;
	int save[2];
	int	ret;

	save[0] = dup(0);
	save[1] = dup(1);
	fd = ft_init_fd(arg);
	if (fd == NULL)
		return (1);
	ret = ft_execute(arg, cmd, env, dir);
	ft_close(fd);
	ft_reverse_fd(save);
	free(fd);
	return (ret);
}
