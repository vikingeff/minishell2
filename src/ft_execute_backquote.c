/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_backquote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 18:39:10 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 13:29:27 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void	lauch_execute_backquote(t_cmd *cmd,
	t_env *env, char *newcmd)
{
	t_list		*arg;
	t_env		c_env;
	t_cmd		c_cmd;
	t_dir		c_dir;

	arg = NULL;
	init_copy_env(&c_env, &c_cmd, &c_dir);
	c_cmd.raw = ft_strdup(newcmd);
	c_cmd.split = NULL;
	c_env.var = env_lst_copy(env);
	c_env.nb = env->nb;
	c_cmd.paths = ft_tab_dup(cmd->paths);
	c_cmd.env = env_list_to_array(c_env.var, c_env.nb);
	arg = ft_parser(c_cmd.raw);
	ft_open_close();
	ft_launcher(&arg, &c_cmd, &c_env, &c_dir);
	if (arg)
		ft_free_arg(&arg);
	ft_free_c_env(&c_env, &c_cmd, &c_dir);
	ft_open_close();
}

static char	*ft_find_quote(t_cmd *cmd, int index, int count)
{
	int		sec;
	char	*newcmd;

	sec = count + 1;
	while (cmd->split[index][sec] && cmd->split[index][sec] != '`')
		sec++;
	newcmd = ft_strsub(cmd->split[index], count + 1, sec - count - 1);
	return (newcmd);
}

static char	*ft_get_quoted(void)
{
	char	*tmp;
	char	*result;
	char	*line;
	int		fd;

	tmp = NULL;
	result = NULL;
	fd = open("/tmp/sh.backquote", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		tmp = ft_strdup(result);
		if (result)
		{
			free(result);
			result = str_join_chr(tmp, line, ' ');
		}
		else
			result = ft_strdup(line);
		if (tmp)
			free(tmp);
		free(line);
	}
	close(fd);
	return (result);
}

static void	ft_new_cmd(t_cmd *cmd, int index, int count)
{
	char	*tmp;
	char	*begin;
	char	*result;

	tmp = NULL;
	result = ft_get_quoted();
	begin = ft_strsub(cmd->split[index], 0, count);
	count++;
	while (cmd->split[index][count] && cmd->split[index][count] != '`')
		count++;
	tmp = ft_strsub(cmd->split[index], count + 1,
		ft_strlen(cmd->split[index]) - 1 - count);
	free(cmd->split[index]);
	cmd->split[index] = ft_strjoin(begin, result);
	free(begin);
	begin = ft_strdup(cmd->split[index]);
	free(cmd->split[index]);
	cmd->split[index] = ft_strjoin(begin, tmp);
	free(begin);
	free(tmp);
	free(result);
}

void		execute_backquote(t_cmd *cmd, t_env *env, t_dir *dir)
{
	int		index;
	int		count;
	char	*newcmd;

	index = 0;
	while (cmd->split[index])
	{
		count = 0;
		while (cmd->split[index][count])
		{
			if (cmd->split[index][count] == '`')
			{
				newcmd = ft_find_quote(cmd, index, count);
				lauch_execute_backquote(cmd, env, newcmd);
				ft_new_cmd(cmd, index, count);
				free(newcmd);
				execute_backquote(cmd, env, dir);
			}
			count++;
		}
		index++;
	}
}
