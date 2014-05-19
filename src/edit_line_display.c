/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 17:57:50 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 13:33:19 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void		refresh_line(t_env *env, t_cur *cur)
{
	ft_putstr("\033[1;34m");
	edit_erase_display(cur);
	ft_putstr(env->prompt);
	ft_putstr("\033[m");
}

static int		stop_display(t_cmd *cmd)
{
	if (!cmd->cmd_end)
		ft_putstr("\033[7m \033[m");
	return (1);
}

void			edit_line_display(t_char *list, t_cur *cur, t_cmd *cmd,\
	t_env *env)
{
	refresh_line(env, cur);
	if (!list)
		if (stop_display(cmd))
			return ;
	while (list->prev)
		list = list->prev;
	while (list)
	{
		if (list->mirror == 1 && !cmd->cmd_end)
			term_put("mr");
		ft_putchar(list->c);
		term_put("me");
		list = list->next;
	}
	if (cur->x == cmd->len && !cmd->cmd_end)
		ft_putstr("\033[7m \033[m");
	if (cmd->cmd_end == 1)
		ft_putchar('\n');
}
