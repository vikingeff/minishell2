/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 14:46:47 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 13:03:41 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

pid_t		g_process_id;

int		ft_main_loop(t_cmd *cmd, t_dir *dir, t_env *env, t_list **arg)
{
	if (!cmd->raw || ft_inib_starter(cmd))
		return (1);
	ft_get_alias(cmd);
	if (*arg)
		ft_free_arg(arg);
	*arg = ft_parser(cmd->raw);
	if (ft_launcher(arg, cmd, env, dir) == -1)
		return (0);
	return (1);
}

int		main(int ac, char **environ)
{
	t_env	env;
	t_dir	dir;
	t_cmd	cmd;
	t_list	*arg;

	arg = NULL;
	g_process_id = -2;
	ft_signal();
	if (ac > 1)
		return (error(0, NULL));
	if (shell_ini(&cmd, &dir, &env, environ))
		return (-1);
	while (!cmd.exit)
	{
		env.prompt = prompt_display(&dir);
		env.prompt_len = ft_strlen(env.prompt);
		term_edit_set(&env);
		command_get(&env, &cmd);
		term_std_set(&env);
		if (!ft_main_loop(&cmd, &dir, &env, &arg))
			return (0);
	}
	delete_temp_free(&arg, &cmd, &env, &dir);
	return (0);
}
