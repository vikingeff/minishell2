/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 12:15:31 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:22:31 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	ft_find_rule(char *str, int index)
{
	if ((index - 1) > 0 && (str[index - 1] == '|'
		|| str[index - 1] == ';' || str[index - 1] == '`'))
		return (1);
	if ((index - 2) > 0)
		if ((str[index - 1] == '&' && str[index - 2] == '&')
			|| (str[index - 1] == '|' && str[index - 2] == '|'))
			return (1);
	if ((index - 1) > 0 && str[index - 1] == '|')
		return (1);
	return (0);
}

int			ft_find_status(char *str, int begin)
{
	int		rule;
	int		index;

	index = 0;
	rule = 1;
	while (str[index] && index <= begin)
	{
		if (!rule)
			rule = ft_find_rule(str, index);
		if (index == 0 || ft_special_char(str[index - 1]))
		{
			if (begin == index)
				return (rule);
			else
				rule = 0;
		}
		index++;
	}
	return (rule);
}

char		**copy_table_i(char **table, int index)
{
	char	**ret;
	int		count;

	count = 0;
	ret = malloc(sizeof(char*) * ft_tablen(table) - index + 1);
	while (table[index])
	{
		ret[count] = ft_strdup(table[index]);
		index++;
		count++;
	}
	ret[count] = NULL;
	return (ret);
}

void		array2d_free(char **array)
{
	int			i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	if (array)
		free(array);
	array = NULL;
}
