/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 18:45:04 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:14:59 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void		ft_delete_char(t_cmd *cmd, int index)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strsub(cmd->raw, 0, index);
	tmp2 = ft_strsub(cmd->raw, index + 1, ft_strlen(cmd->raw) - (index + 1));
	free(cmd->raw);
	cmd->raw = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
}
