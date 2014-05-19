/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 12:13:42 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 13:35:37 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static char	*return_completion(glob_t *globbuf, char *tmp, char *ret)
{
	free(tmp);
	globfree(globbuf);
	return (ret);
}

static char	*fill_completion_arg(t_cmd *cmd, char *str, int flag)
{
	glob_t		globbuf;
	char		*ret;
	char		*tmp;

	tmp = ft_strjoin(str, "*");
	if (glob(tmp, GLOB_MARK | GLOB_ERR, NULL, &globbuf))
		return (return_completion(&globbuf, tmp, NULL));
	ret = ft_strdup(globbuf.gl_pathv[cmd->comp]);
	if (!flag)
		cmd->comp = 0;
	else
		cmd->comp++;
	if (flag && cmd->comp == (int)globbuf.gl_pathc)
		cmd->comp = 0;
	if (globbuf.gl_pathc == 1)
		reset_comp(cmd);
	return (return_completion(&globbuf, tmp, ret));
}

static void	init_comp_bin(glob_t *globbuf, t_cmd *cmd, char *tmp)
{
	int			index;
	char		*concat;

	index = -1;
	while (cmd->paths[++index])
	{
		concat = str_join_chr(cmd->paths[index], tmp, '/');
		if (index == 0)
			glob(concat, GLOB_MARK | GLOB_ERR, NULL, globbuf);
		else
			glob(concat, GLOB_APPEND | GLOB_MARK | GLOB_ERR, NULL, globbuf);
		free(concat);
	}
}

static char	*fill_completion_bin(t_cmd *cmd, char *str, int flag)
{
	glob_t		globbuf;
	char		*ret;
	char		**table;
	char		*tmp;

	if ((str[0] && str[0] == '/') || (str[1] && str[1] == '/'))
		return (fill_completion_arg(cmd, str, flag));
	tmp = ft_strjoin(str, "*");
	init_comp_bin(&globbuf, cmd, tmp);
	if (globbuf.gl_pathc == 0)
		return (return_completion(&globbuf, tmp, NULL));
	table = ft_strsplit(globbuf.gl_pathv[cmd->comp], '/');
	ret = ft_strdup(table[ft_tablen(table) - 1]);
	if (!flag)
		cmd->comp = 0;
	else
		cmd->comp++;
	if (flag && cmd->comp == (int)globbuf.gl_pathc)
		cmd->comp = 0;
	if (globbuf.gl_pathc == 1)
		reset_comp(cmd);
	array2d_free(table);
	return (return_completion(&globbuf, tmp, ret));
}

char		*fill_completion(t_cmd *cmd, char *str, int status, int flag)
{
	if (cmd->comp == -1)
		cmd->comp++;
	if (status == 0)
		return (fill_completion_arg(cmd, str, flag));
	else
		return (fill_completion_bin(cmd, str, flag));
}
