/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 15:58:46 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:13:59 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void		k_enter(t_cmd *cmd)
{
	cmd->cmd_end = 1;
}

void		k_esc(t_cmd *cmd)
{
	cmd->cmd_end = 1;
	cmd->exit = 1;
}

void		k_del(t_cmd *cmd, t_cur *cursor, t_char **list)
{
	if (cmd->len > 0 && cursor->x < cmd->len)
	{
		k_right(cmd, cursor, list);
		k_bckspc(cmd, cursor, list);
	}
}

void		k_bckspc(t_cmd *cmd, t_cur *cursor, t_char **list)
{
	if (cursor->x != cmd->len &&
		(cursor->prompt_len + cmd->len) % cursor->term_len == 0)
		cursor->nb_line -= 1;
	if (cursor->x > 1)
	{
		(*list)->mirror = 0;
		if ((*list)->prev)
			(*list)->prev->mirror = 1;
		*list = edit_char_del(*list, cmd, cursor);
	}
	else if (cursor->x == 1)
	{
		*list = edit_char_del(*list, cmd, cursor);
	}
}
