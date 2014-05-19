/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 10:16:45 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 13:33:39 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <shell.h>

void			space_padding(int index)
{
	int			sz;
	int			max;
	char		*tmp;

	tmp = ft_itoa(index);
	sz = ft_strlen(tmp);
	max = 5;
	while (max > sz)
	{
		ft_putchar(' ');
		max--;
	}
	free(tmp);
}

int				print_hist(t_cmd *cmd)
{
	t_hist		*save;
	int			nb;

	save = cmd->hist;
	nb = hist_is_valid(cmd);
	if (!save || nb <= 0)
		return (1);
	while (save->prev && nb > 1)
	{
		save = save->prev;
		nb--;
	}
	while (save)
	{
		space_padding(save->index);
		ft_putnbr(save->index);
		ft_putstr("  ");
		if (cmd->split[1])
			if (!(ft_strcmp(cmd->split[1], "-t")))
				ft_putstr(save->time);
		ft_putstr(save->data);
		ft_putchar('\n');
		save = save->next;
	}
	return (0);
}

char			*time_to_char(const struct tm *time)
{
	char		*res;

	res = ft_itoa(time->tm_year + 1900);
	res = ft_strjoin_free(res, "/");
	res = ft_strjoin_double_free(res, time_padding(ft_itoa(time->tm_mon)));
	res = ft_strjoin_free(res, "/");
	res = ft_strjoin_double_free(res, time_padding(ft_itoa(time->tm_mday)));
	res = ft_strjoin_free(res, " ");
	res = ft_strjoin_double_free(res, time_padding(ft_itoa(time->tm_hour)));
	res = ft_strjoin_free(res, ":");
	res = ft_strjoin_double_free(res, time_padding(ft_itoa(time->tm_min)));
	res = ft_strjoin_free(res, ":");
	res = ft_strjoin_double_free(res, time_padding(ft_itoa(time->tm_sec)));
	res = ft_strjoin_free(res, " ");
	return (res);
}

static t_hist	*add_elem(t_hist *elem, char *data, char *time, int index)
{
	t_hist		*new_elem;

	new_elem = malloc(sizeof(*new_elem));
	if (new_elem)
	{
		new_elem->size = ft_strlen(data);
		new_elem->data = ft_strdup(data);
		new_elem->time = ft_strdup(time);
		new_elem->index = index;
		new_elem->next = NULL;
		new_elem->prev = elem;
		elem->next = new_elem;
	}
	return (new_elem);
}

t_hist			*list_filling(t_hist *hist, char *data)
{
	static int	index = 0;
	time_t		rawtime;
	struct tm	*timeinfo;
	char		*tmp;

	index++;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	if (hist)
	{
		tmp = time_to_char(timeinfo);
		hist = add_elem(hist, data, tmp, index);
		free(tmp);
	}
	else
	{
		hist = (t_hist*)malloc(sizeof(t_hist));
		hist->data = ft_strdup(data);
		hist->time = time_to_char(timeinfo);
		hist->index = index;
		hist->size = ft_strlen(data);
		hist->prev = NULL;
		hist->next = NULL;
	}
	return (hist);
}
