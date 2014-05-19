/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_char_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 16:22:36 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:14:21 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void		connection_next(t_char **list, t_char **list_tmp)
{
	if ((*list)->next->prev)
	{
		(*list)->next->prev = (*list)->prev;
		*list_tmp = (*list)->next;
	}
	else
		(*list)->next->prev = NULL;
}

static void		connection_prev(t_char **list, t_char **list_tmp)
{
	if ((*list)->prev->next)
	{
		(*list)->prev->next = (*list)->next;
		*list_tmp = (*list)->prev;
	}
	else
		(*list)->prev->next = NULL;
}

t_char			*edit_char_del(t_char *list, t_cmd *cmd, t_cur *cursor)
{
	t_char		*list_tmp;

	list_tmp = NULL;
	if (!list)
		return (list);
	if (list->next)
		connection_next(&list, &list_tmp);
	if (list->prev)
		connection_prev(&list, &list_tmp);
	free(list);
	list = NULL;
	cmd->len--;
	cursor->x -= 1;
	return (list_tmp);
}
