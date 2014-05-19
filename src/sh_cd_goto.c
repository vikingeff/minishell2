/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd_goto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 18:18:11 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 17:18:22 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char		*get_newpath(char **modif, t_dir *dir, char *curpath)
{
	char		*tmp;
	int			i;

	curpath = ft_strdup(dir->pwd);
	i = -1;
	tmp = NULL;
	while (modif[++i])
	{
		if (curpath)
		{
			tmp = ft_strdup(curpath);
			free(curpath);
		}
		if (!(curpath = newpath_write(tmp, modif[i])))
		{
			free(tmp);
			return (NULL);
		}
		if (tmp)
			free(tmp);
	}
	return (curpath);
}

char		*newpath_write(char *curpath, char *modif)
{
	char		*newpath;
	char		**split;

	newpath = NULL;
	split = NULL;
	if (modif[0] != '.' || (ft_strlen(modif) > 3 && modif[0] == '.'
		&& modif[1] == '.' && modif[2] == '.'))
		newpath = str_join_chr(curpath, modif, '/');
	else if (modif[1] == '.' && ft_strcmp(curpath, "/"))
	{
		split = ft_strsplit(curpath, '/');
		newpath = get_path(newpath, split);
		array2d_free(split);
	}
	else
		newpath = ft_strdup(curpath);
	if (newpath && access(newpath, F_OK))
	{
		error(33, newpath);
		free(newpath);
		array2d_free(split);
		return (NULL);
	}
	return (newpath);
}

char		*get_path(char *newpath, char **split)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = NULL;
	while (split[i + 1])
	{
		if (newpath)
		{
			tmp = ft_strdup(newpath);
			free(newpath);
		}
		newpath = str_join_chr(tmp, split[i], '/');
		if (tmp)
			free(tmp);
		i++;
	}
	return (newpath);
}
