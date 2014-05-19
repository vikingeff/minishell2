/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 15:58:15 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:21:21 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int					sh_unalias(t_cmd *cmd)
{
	int		index;
	t_list	*alias;

	index = 1;
	while (cmd->split[index])
	{
		alias = ft_find_list(cmd->alias, cmd->split[index]);
		if (alias)
		{
			if (alias == cmd->alias)
				cmd->alias = cmd->alias->next;
			if (alias->prev)
				alias->prev->next = alias->next;
			if (alias->next)
				alias->next->prev = alias->prev;
			free(alias->mot);
			free(alias->valeure);
			free(alias);
		}
		index++;
	}
	return (0);
}
