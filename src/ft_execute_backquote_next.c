/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_backquote_next.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 17:31:19 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 17:44:33 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static char	*ft_free_and_join(char *tmp, char *begin, char *ended, char *start)
{
	tmp = ft_strdup(begin);
	free(begin);
	begin = str_join_chr(ended, tmp, ' ');
	free(ended);
	free(tmp);
	tmp = ft_strdup(begin);
	free(begin);
	begin = str_join_chr(start, tmp, ' ');
	free(tmp);
	return (begin);
}

char		**ft_get_end(t_cmd *cmd, int index, int count, char *start)
{
	char	*begin;
	char	*tmp;
	char	*ended;
	char	**table;

	begin = NULL;
	tmp = NULL;
	ended = ft_strsub(cmd->split[index], count + 1,
		ft_strlen(cmd->split[index]) - count - 1);
	index++;
	while (cmd->split[index])
	{
		free(tmp);
		tmp = ft_strdup(begin);
		free(begin);
		begin = str_join_chr(tmp, cmd->split[index], ' ');
		index++;
	}
	free(tmp);
	begin = ft_free_and_join(tmp, begin, ended, start);
	table = ft_strsplit_all(begin);
	return (table);
}

char		*ft_get_begin(t_cmd *cmd, int index, int count)
{
	char	*begin;
	char	*tmp;
	char	*ended;
	int		start;

	begin = NULL;
	tmp = NULL;
	start = 0;
	while (start < index)
	{
		free(tmp);
		tmp = ft_strdup(begin);
		free(begin);
		begin = str_join_chr(tmp, cmd->split[start], ' ');
		start++;
	}
	free(tmp);
	tmp = ft_strdup(begin);
	ended = ft_strsub(cmd->split[start], 0, count);
	free(begin);
	begin = str_join_chr(tmp, ended, ' ');
	free(ended);
	return (begin);
}
