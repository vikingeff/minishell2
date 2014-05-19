/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_chr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 17:47:36 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 13:34:10 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	hist_chr_is_valid(t_cmd *cmd, t_hist *save)
{
	int			i;
	char		*str;

	i = 1;
	str = NULL;
	if (cmd->split[1])
		return (error(32, "!"));
	else if (ft_isdigit(cmd->split[0][i]))
	{
		while (ft_isdigit(cmd->split[0][i]) && (cmd->split[0][i]))
			i++;
		if ((int)ft_strlen(cmd->split[0]) == i)
		{
			str = ft_strsub(cmd->split[0], 1, ft_strlen(cmd->split[0]));
			i = ft_atoi(str);
			if (i > save->index)
				return (error(34, cmd->split[0]));
			free(str);
			return (i);
		}
		else
			return (0);
	}
	return (0);
}

static int	hist_match_loop(char *str, t_hist *save, int cmd)
{
	char		*sml;
	int			len;

	len = ft_strlen(str);
	if (!save->prev)
		return (-1);
	while (save)
	{
		sml = ft_strsub(save->data, 0, len);
		if (!(ft_strcmp(sml, str)))
		{
			free(sml);
			cmd = save->index;
			return (cmd);
		}
		free(sml);
		save = save->prev;
	}
	return (cmd);
}

static int	hist_match(char *str, t_hist *save)
{
	static int	cmd = 0;
	static char	*tmp = NULL;

	if (str)
	{
		if (tmp)
		{
			if (!ft_strcmp(str, tmp))
				cmd = 0;
		}
		cmd = hist_match_loop(str, save, cmd);
		if (cmd == -1)
		{
			tmp = str;
			return (error(666, str));
		}
		tmp = str;
	}
	else
		tmp = NULL;
	return (cmd);
}

int			hist_chr(t_cmd *cmd, t_dir *dir, t_env *env)
{
	t_hist		*save;
	char		*str;
	int			cmd_i;

	str = NULL;
	save = cmd->hist;
	if (!save)
		return (error(34, cmd->split[0]));
	cmd_i = hist_chr_is_valid(cmd, save);
	if (cmd_i == 0)
		str = ft_strsub(cmd->split[0], 1, ft_strlen(cmd->split[0]));
	while (save)
	{
		if (cmd_i == 0)
			cmd_i = hist_match(str, save);
		if (cmd_i && cmd_i == save->index)
		{
			ft_putendl(save->data);
			ft_lauch_history(cmd, dir, env, save->data);
		}
		save = save->prev;
	}
	free(str);
	return (0);
}
