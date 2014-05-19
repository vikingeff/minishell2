/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_navigation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 17:00:00 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:14:02 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	cursor_reset(t_cur *cursor)
{
	cursor->x = 0;
	cursor->y = 1;
	cursor->line_x = cursor->prompt_len;
	return (-1);
}

static void	restore_current(t_cmd *cmd, t_cur *cursor, t_char **list)
{
	int			i;

	i = -1;
	while (cmd->save_cur[++i])
	{
		*list = edit_char_add(*list, cmd->save_cur[i], cursor, cmd);
		(*list)->mirror = 0;
	}
	free(cmd->save_cur);
	cmd->save_cur = NULL;
}

static void	nav_up(t_cmd *cmd, t_cur *cursor, t_char **list)
{
	int		i;
	char	*trash;

	i = -1;
	if (!cmd->nav)
		return ;
	if (*list)
	{
		trash = edit_list_to_str(*list, cmd, cursor);
		free(trash);
		*list = NULL;
	}
	i = cursor_reset(cursor);
	while (cmd->nav->data[++i])
	{
		*list = edit_char_add(*list, cmd->nav->data[i], cursor, cmd);
		(*list)->mirror = 0;
	}
	if (cmd->nav->prev)
		cmd->nav = cmd->nav->prev;
}

static void	nav_down(t_cmd *cmd, t_cur *cursor, t_char **list)
{
	int		i;
	char	*trash;

	if (!cmd->nav)
		return ;
	if (*list)
	{
		trash = edit_list_to_str(*list, cmd, cursor);
		free(trash);
		*list = NULL;
	}
	i = cursor_reset(cursor);
	if (cmd->nav->next)
	{
		cmd->nav = cmd->nav->next;
		while (cmd->nav->data[++i])
		{
			*list = edit_char_add(*list, cmd->nav->data[i], cursor, cmd);
			(*list)->mirror = 0;
		}
	}
	else if (cmd->save_cur)
		restore_current(cmd, cursor, list);
	else
		ft_putstr("\033[7m \033[m");
}

void		hist_navig(long key[], t_cmd *cmd, t_cur *cursor, t_char **list)
{
	if (UP)
	{
		if (cmd->save_cur == NULL)
		{
			cmd->save_cur = edit_list_to_str(*list, cmd, cursor);
			*list = NULL;
		}
		nav_up(cmd, cursor, list);
	}
	else if (DOWN)
	{
		nav_down(cmd, cursor, list);
	}
}
