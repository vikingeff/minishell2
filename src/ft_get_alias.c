/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 19:51:45 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:15:27 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

t_list		*ft_find_list(t_list *list, char *str)
{
	t_list	*find;

	find = list;
	while (find)
	{
		if (ft_strcmp(find->mot, str) == 0)
			return (find);
		find = find->next;
	}
	return (NULL);
}

int			ft_find_rule(char *str, int index)
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

void		ft_init_alias(t_cmd *cmd, char **tmp, t_list *alias, int index)
{
	char	*end;

	free(tmp[0]);
	tmp[0] = ft_strdup(alias->valeure);
	end = ft_strsub(cmd->raw, 0, index);
	free(cmd->raw);
	cmd->raw = ft_strdup(end);
	free(end);
}

int			ft_find_alias(t_cmd *cmd, int index)
{
	char	**tmp;
	char	*end;
	t_list	*alias;

	end = ft_strsub(cmd->raw, index, ft_strlen(cmd->raw) - index);
	tmp = ft_strsplit_all(end);
	free(end);
	if ((alias = ft_find_list(cmd->alias, tmp[0])))
	{
		ft_init_alias(cmd, tmp, alias, index);
		index = 0;
		while (tmp[index])
		{
			end = ft_strdup(cmd->raw);
			free(cmd->raw);
			cmd->raw = str_join_chr(end, tmp[index], ' ');
			free(end);
			index++;
		}
		array2d_free(tmp);
		return (1);
	}
	array2d_free(tmp);
	return (0);
}

void		ft_get_alias(t_cmd *cmd)
{
	int	index;
	int	rule;

	rule = 1;
	index = 0;
	if (!cmd->alias)
		return ;
	while (cmd->raw[index])
	{
		if (!rule)
		{
			rule = ft_find_rule(cmd->raw, index);
			index++;
		}
		if (rule && ft_find_alias(cmd, index))
		{
			rule = 1;
			index = 0;
		}
		else
		{
			rule = 0;
			index++;
		}
	}
}
