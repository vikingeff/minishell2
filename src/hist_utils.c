/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 15:47:53 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:19:29 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <shell.h>

char	*ft_strjoin_free(char *res, char *str)
{
	char		*tmp;

	tmp = ft_strdup(res);
	free(res);
	res = ft_strjoin(tmp, str);
	free(tmp);
	return (res);
}

char	*ft_strjoin_double_free(char *res, char *str)
{
	char		*tmp;

	tmp = ft_strdup(res);
	free(res);
	res = ft_strjoin(tmp, str);
	free(tmp);
	free(str);
	return (res);
}

char	*time_padding(char *src)
{
	int			sz;
	char		*zero;
	char		*dest;

	zero = "0";
	sz = ft_strlen(src);
	if (sz != 2)
	{
		dest = ft_strjoin(zero, src);
		free(src);
		return (dest);
	}
	else
		return (src);
}

void	del_hist(t_cmd *cmd)
{
	t_hist		*tmp;

	while (cmd->hist)
	{
		free(cmd->hist->time);
		free(cmd->hist->data);
		cmd->hist->data = NULL;
		cmd->hist->time = NULL;
		tmp = cmd->hist->prev;
		free(cmd->hist);
		cmd->hist = NULL;
		cmd->hist = tmp;
	}
	cmd->hist = NULL;
}

int		hist_is_valid(t_cmd *cmd)
{
	if (cmd->split[1])
	{
		if (!(ft_strcmp(cmd->split[1], "-c")))
		{
			del_hist(cmd);
			return (-1);
		}
		else if (!(ft_strcmp(cmd->split[1], "-t")))
		{
			if (cmd->split[2] && (ft_isdigit(cmd->split[2][0])))
				return (ft_atoi(cmd->split[2]));
			else
				return (17);
		}
		else if (ft_isdigit(cmd->split[1][0]))
			return (ft_atoi(cmd->split[1]));
		else
			return (error(7, NULL));
	}
	return (17);
}
