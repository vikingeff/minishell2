/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 19:07:35 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:16:37 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void	ft_get_signal(int n)
{
	t_cmd	*cmd;

	if (n == SIGINT)
	{
		if (kill(g_process_id, SIGINT) == -1)
		{
			cmd = ft_remember(NULL, NULL, NULL, 1);
			cmd->sig = 1;
			cmd->fdsave = dup(0);
			close(0);
		}
	}
}

void		ft_signal(void)
{
	signal(SIGINT, ft_get_signal);
}
