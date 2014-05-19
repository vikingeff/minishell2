/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array_to_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 17:24:21 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:14:16 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static char		*str_parse_name(char *var)
{
	char		*name;
	int			var_len;
	int			i;

	i = 0;
	name = NULL;
	var_len = ft_strlen(var);
	while (var[i] != '=' && i < var_len)
		i++;
	if (!(name = (char*)malloc(sizeof(char) * (i + 1))))
	{
		error(15, "env_get_name()");
		return (NULL);
	}
	i = 0;
	while (var[i] != '=')
	{
		name[i] = var[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static char		*str_parse_value(char *var)
{
	char		*value;
	int			var_len;
	int			start;
	int			i;

	i = 0;
	start = 0;
	value = NULL;
	var_len = ft_strlen(var);
	while (var[start - 1] != '=' && i < var_len)
		start++;
	while (var[start + i])
		i++;
	if (!(value = (char *)malloc(sizeof(char) * (i + 1))))
	{
		error(15, "env_get_value()");
		return (NULL);
	}
	i = -1;
	while (var[start + ++i])
		value[i] = var[start + i];
	value[i] = '\0';
	return (value);
}

t_var			*env_array_to_list(t_env *env)
{
	t_var		*list;
	t_var		*start;
	int			i;

	i = 2;
	list = NULL;
	start = NULL;
	while (env->raw[i])
	{
		if (env_list_add(&list, &start))
			return (NULL);
		list->name = str_parse_name(env->raw[i]);
		list->value = str_parse_value(env->raw[i]);
		i++;
	}
	env->nb = i - 1;
	list = start;
	return (list);
}
