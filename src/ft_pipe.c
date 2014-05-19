/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 19:03:38 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:16:32 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	ft_create_pipe(int *fdpipe, int pipenb, int *count)
{
	int	index;

	index = 0;
	*count = 0;
	while (index < pipenb)
	{
		pipe(fdpipe + index * 2);
		index++;
	}
	return (0);
}

static int	ft_pipe1(int fd[2], t_list *arg, int *fdpipe, int count)
{
	if (ft_strcmp(arg->valeure, ";") != 0)
		ft_dup2(fdpipe[count + 1], 1);
	else
	{
		fd[1] = ft_get_fd(arg->dir);
		ft_dup2(fd[1], 1);
	}
	return (fd[1]);
}

static int	ft_pipe0(int fd[2], t_list *arg, int *fdpipe, int count)
{
	if (count != 0)
		ft_dup2(fdpipe[count - 2], 0);
	else
	{
		fd[0] = ft_get_fd(arg->dir);
		ft_dup2(fd[0], 0);
	}
	return (fd[0]);
}

static void	ft_wait_pipe(int pipenb)
{
	int	index;

	index = 0;
	while (index < (pipenb + 1))
	{
		wait(NULL);
		index++;
	}
}

t_list		*ft_pipe(t_list *arg, t_dir *dir, t_env *env, t_cmd *cmd)
{
	int		count;
	pid_t	pid;
	int		fdpipe[2 * arg->pipenb];
	int		fd[2];
	int		pipenb;

	fd[1] = ft_init_pipe(arg->pipenb, &pipenb);
	fd[0] = ft_create_pipe(fdpipe, arg->pipenb, &count);
	while (count < pipenb * 2 + 2)
	{
		if ((pid = fork()) == 0)
		{
			fd[1] = ft_pipe1(fd, arg, fdpipe, count);
			fd[0] = ft_pipe0(fd, arg, fdpipe, count);
			ft_close_pipe(fdpipe, pipenb);
			if (fd[1] != -1 && fd[0] != -1)
				ft_execute_no_wait(arg, cmd, env, dir);
			exit(0);
		}
		arg = arg->next;
		count = count + 2;
	}
	ft_close_pipe(fdpipe, pipenb);
	ft_wait_pipe(pipenb);
	return (ft_close_arg(fd, arg));
}
