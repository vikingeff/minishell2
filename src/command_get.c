/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 20:45:37 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 13:32:30 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void		edit_ini(t_cur *cur, t_env *env, t_cmd *cmd, t_char **list)
{
	if (cmd->raw)
	{
		free(cmd->raw);
		cmd->raw = NULL;
	}
	cur->x = 0;
	cur->line_x = 0;
	cur->y = 1;
	cur->nb_line = 1;
	cur->prompt_len = env->prompt_len;
	cur->term_len = env->term_len;
	cmd->cmd_end = 0;
	cmd->len = 0;
	*list = NULL;
	cmd->nav = cmd->hist;
	free(cmd->save_cur);
	cmd->save_cur = NULL;
	ft_putstr("\033[7m \033[m");
}

static void		edit_update(t_env *env, t_cur *cur, t_cmd *cmd)
{
	char	*n_term;

	n_term = env_get_value("TERM", env);
	tgetent(NULL, n_term);
	tcgetattr(0, env->term);
	env->term_len = tgetnum("co");
	cur->term_len = env->term_len;
	cur->line_x = (cur->x + cur->prompt_len) % cur->term_len;
	cur->y = ((cur->x + cur->prompt_len) / cur->term_len) + 1;
	cur->nb_line = ((cur->prompt_len + cmd->len) / (cur->term_len)) + 1;
}

static int		edit_signal(t_cur *cur, t_env *env, t_cmd *cmd, t_char **list)
{
	char		*trash;

	trash = NULL;
	cmd->sig = 0;
	cmd->cmd_end = 2;
	edit_line_display(*list, cur, cmd, env);
	trash = edit_list_to_str(*list, cmd, cur);
	*list = NULL;
	free(trash);
	ft_dup2(cmd->fdsave, 0);
	return (1);
}

static void		command_set(t_cur *cur, t_env *env, t_cmd *cmd,\
	t_char **list)
{
	if (*list)
	{
		cmd->raw = edit_list_to_str(*list, cmd, cur);
		*list = NULL;
	}
	else
		ft_putchar('\n');
	if (filling_checking(cmd))
		cmd->hist = list_filling(cmd->hist, cmd->raw);
	free(env->prompt);
	env->prompt = NULL;
}

void			command_get(t_env *env, t_cmd *cmd)
{
	t_char		*list;
	t_cur		cur;

	edit_ini(&cur, env, cmd, &list);
	edit_line_display(list, &cur, cmd, env);
	while (!cmd->cmd_end)
	{
		env->key[0] = 0;
		read(0, env->key, 10);
		if (cmd->sig)
			if (edit_signal(&cur, env, cmd, &list))
				continue ;
		edit_update(env, &cur, cmd);
		if (!edit_key(env->key, cmd, &cur, &list))
			list = edit_char_add(list, env->key[0], &cur, cmd);
		if (list && cur.x > 0)
			list->mirror = 0;
		edit_line_display(list, &cur, cmd, env);
	}
	command_set(&cur, env, cmd, &list);
}
