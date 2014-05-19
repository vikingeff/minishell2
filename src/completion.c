/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 17:45:19 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:12:43 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void		init_completion(t_char **list, t_cmd *cmd, t_cur *cur)
{
	char	*trash;

	if (cmd->s_cursor == -1)
		cmd->s_cursor = cur->x - 1;
	while ((*list)->next)
		k_right(cmd, cur, list);
	if (cmd->actual == NULL)
	{
		cmd->actual = edit_list_to_str(*list, cmd, cur);
		*list = NULL;
	}
	else
	{
		trash = edit_list_to_str(*list, cmd, cur);
		*list = NULL;
		free(trash);
	}
}

static int		get_begin(char *str, int cur)
{
	int	index;

	index = cur;
	while (index >= 0)
	{
		if (ft_special_char(str[index]))
			return (index + 1);
		index--;
	}
	return (0);
}

static void		free_comp(t_comp *comp, t_cmd *cmd, t_cur *cur,\
	t_char **list)
{
	comp->i = -1;
	*list = NULL;
	while (comp->word[++comp->i])
	{
		*list = edit_char_add(*list, comp->word[comp->i], cur, cmd);
		(*list)->mirror = 0;
	}
	free(comp->word);
	free(comp->tmp);
	free(comp->final);
	free(comp->end);
	while (comp->i > comp->f_len)
	{
		k_left(cur, list);
		comp->i--;
	}
}

void			completion(t_cmd *cmd, t_cur *cur, t_char **list, int flag)
{
	t_comp	comp;

	comp.final = NULL;
	if (!*list)
		return ;
	init_completion(list, cmd, cur);
	comp.begin = get_begin(cmd->actual, cmd->s_cursor);
	comp.status = ft_find_status(cmd->actual, comp.begin);
	comp.word = ft_strsub(cmd->actual, comp.begin,
		cmd->s_cursor - comp.begin + 1);
	comp.end = ft_strsub(cmd->actual, cmd->s_cursor + 1,
		ft_strlen(cmd->actual) - cmd->s_cursor);
	comp.tmp = ft_strsub(cmd->actual, 0, comp.begin);
	comp.final = fill_completion(cmd, comp.word, comp.status, flag);
	if (!comp.final)
		comp.final = ft_strdup(comp.word);
	free(comp.word);
	comp.word = ft_strjoin(comp.tmp, comp.final);
	comp.f_len = ft_strlen(comp.word);
	free(comp.tmp);
	comp.tmp = ft_strdup(comp.word);
	free(comp.word);
	comp.word = ft_strjoin(comp.tmp, comp.end);
	free_comp(&comp, cmd, cur, list);
}
