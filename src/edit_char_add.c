/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_char_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 16:17:05 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:14:21 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static t_char	*to_front(t_char **nchr, t_char **lst, t_cmd *cmd, t_cur *cur)
{
	if ((*lst)->prev)
	{
		(*nchr)->prev = (*lst)->prev;
		(*lst)->prev->next = *nchr;
	}
	(*lst)->prev = *nchr;
	(*lst) = *nchr;
	cmd->len++;
	cur->x += 1;
	return ((*lst));
}

static void		to_back(t_char **nchr, t_char **list, t_cmd *cmd, t_cur *cur)
{
	if (*list)
	{
		if ((*list)->next)
		{
			(*nchr)->next = (*list)->next;
			(*list)->next->prev = *nchr;
		}
	}
	(*nchr)->prev = *list;
	(*list)->next = *nchr;
	if (cur->x != cmd->len && (cur->prompt_len + cmd->len) % cur->term_len == 0)
		cur->nb_line -= 1;
}

t_char			*edit_char_add(t_char *list, long chr, t_cur *cur, t_cmd *cmd)
{
	t_char		*nchr;

	nchr = NULL;
	if (!(nchr = (t_char *)malloc(sizeof(t_char))))
		return (NULL);
	nchr->c = (int)chr;
	nchr->mirror = 1;
	nchr->nl = 0;
	nchr->next = NULL;
	if (cur->x == 0)
	{
		nchr->next = list;
		nchr->prev = NULL;
		if (list)
			return (to_front(&nchr, &list, cmd, cur));
	}
	else
		to_back(&nchr, &list, cmd, cur);
	cmd->len++;
	cur->x += 1;
	return (nchr);
}
