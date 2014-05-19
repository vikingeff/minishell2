/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_list_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 09:15:42 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:14:17 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static char		*to_str(t_char *list)
{
	char		*str;
	char		*temp;
	char		c[2];

	str = NULL;
	temp = NULL;
	c[0] = '\0';
	c[1] = '\0';
	while (list->prev)
		list = list->prev;
	while (list)
	{
		c[0] = (char)list->c;
		if (str)
			free(str);
		str = ft_strjoin(temp, c);
		if (temp)
			free(temp);
		temp = ft_strdup(str);
		list = list->next;
	}
	free(temp);
	return (str);
}

char			*edit_list_to_str(t_char *list, t_cmd *cmd, t_cur *cursor)
{
	char		*str;

	str = NULL;
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	str = to_str(list);
	while (list->prev)
		list = edit_char_del(list, cmd, cursor);
	list = edit_char_del(list, cmd, cursor);
	return (str);
}
