/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_jump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 17:45:21 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:14:01 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			ft_special_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

void		k_jump_first(t_cur *cursor, t_char **list)
{
	while (cursor->x != 0)
		k_left(cursor, list);
}

void		k_jump_last(t_cmd *cmd, t_cur *cursor, t_char **list)
{
	while (cursor->x < cmd->len)
		k_right(cmd, cursor, list);
}

void		k_jump_word_prev(t_cur *cursor, t_char **list)
{
	if (*list && ft_special_char((*list)->c) && (*list)->prev->c)
	{
		while (cursor->x != 0 && ft_special_char((*list)->c))
			k_left(cursor, list);
	}
	while (cursor->x != 0 && !ft_special_char((*list)->c))
		k_left(cursor, list);
}

void		k_jump_word_next(t_cmd *cmd, t_cur *cursor, t_char **list)
{
	if (*list && (*list)->next && ft_special_char((*list)->next->c)
		&& (*list)->next->c)
	{
		while (*list && (*list)->next && ft_special_char((*list)->next->c)
				&& (*list)->next->c)
			k_right(cmd, cursor, list);
		return ;
	}
	while (*list && (*list)->next && !ft_special_char((*list)->next->c)
			&& (*list)->next->c)
		k_right(cmd, cursor, list);
	while (*list && (*list)->next && ft_special_char((*list)->next->c)
			&& (*list)->next->c)
		k_right(cmd, cursor, list);
}
