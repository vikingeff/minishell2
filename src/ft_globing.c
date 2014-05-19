/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_globing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 16:15:27 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:15:34 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char	*ft_get_globing(char *str)
{
	glob_t		globbuf;
	char		*ret;
	char		*tmp;
	int			index;

	if (glob(str, GLOB_NOMAGIC | GLOB_ERR, NULL, &globbuf))
		return (ft_strdup(str));
	ret = NULL;
	tmp = NULL;
	index = 0;
	while (globbuf.gl_pathv[index])
	{
		tmp = ft_strdup(ret);
		free(ret);
		ret = str_join_chr(tmp, globbuf.gl_pathv[index], ' ');
		free(tmp);
		index++;
	}
	globfree(&globbuf);
	return (ret);
}

void	ft_globing(t_cmd *cmd)
{
	char	*tmp;
	char	*ret;
	char	*globing;
	int		index;

	index = 0;
	tmp = NULL;
	ret = NULL;
	while (cmd->split[index])
	{
		tmp = ft_strdup(ret);
		free(ret);
		globing = ft_get_globing(cmd->split[index]);
		ret = str_join_chr(tmp, globing, ' ');
		free(globing);
		free(tmp);
		index++;
	}
	array2d_free(cmd->split);
	cmd->split = ft_strsplit_all(ret);
	free(ret);
}
