/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_direct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 18:33:26 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:16:14 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	ft_return_of_the_wood(t_list *arg, int index, char *tmp)
{
	char	*result;

	if (tmp[index] == '>' && tmp[index + 1] == '>'
		&& (result = ft_modify_arg(arg, index + 1, 1)) != NULL)
		arg->dir = ft_add_arg(">>", result, arg->dir);
	else if (tmp[index] == '<' && tmp[index + 1] == '<'
		&& (result = ft_modify_arg(arg, index + 1, 1)) != NULL)
		arg->dir = ft_add_arg("<<", result, arg->dir);
	else if (tmp[index] == '>'
		&& (result = ft_modify_arg(arg, index, 0)) != NULL)
		arg->dir = ft_add_arg(">", result, arg->dir);
	else if (tmp[index] == '<' &&
		(result = ft_modify_arg(arg, index, 0)) != NULL)
		arg->dir = ft_add_arg("<", result, arg->dir);
	else
		return (index + 1);
	free(result);
	return (0);
}

static void	ft_find_direct(t_list *arg)
{
	char	*tmp;
	int		index;

	tmp = arg->mot;
	arg->dir = NULL;
	index = 0;
	while (tmp[index])
	{
		tmp = arg->mot;
		index = ft_return_of_the_wood(arg, index, tmp);
	}
}

static int	ft_wood(t_list *arg, int in, int out)
{
	if (ft_strcmp(arg->valeure, ";") == 0 && (arg->prev == NULL ||
		(arg->prev != NULL && ft_strcmp(arg->prev->valeure, ";") == 0))
		&& (in > 1 || out > 1))
		return (1);
	else if (ft_strcmp(arg->valeure, "|") == 0 && arg->prev != NULL &&
		ft_strcmp(arg->prev->valeure, "|") == 0 && (in > 0 || out > 0))
		return (1);
	else if (ft_strcmp(arg->valeure, ";") == 0 && arg->prev != NULL &&
		ft_strcmp(arg->prev->valeure, "|") == 0 && (in > 0 || out > 1))
		return (1);
	else if (ft_strcmp(arg->valeure, "|") == 0 && (arg->prev == NULL ||
		(arg->prev != NULL && ft_strcmp(arg->prev->valeure, ";") == 0))
		&& (in > 1 || out > 0))
		return (1);
	return (0);
}

static int	ft_check_direct(t_list *arg)
{
	t_list	*save;
	int		out;
	int		in;

	in = 0;
	out = 0;
	save = arg->dir;
	while (save)
	{
		if (ft_strcmp(save->mot, ">") == 0 || ft_strcmp(save->mot, ">>") == 0)
			out++;
		if (ft_strcmp(save->mot, "<") == 0 || ft_strcmp(save->mot, "<<") == 0)
			in++;
		save = save->next;
	}
	return (ft_wood(arg, in, out));
}

t_list		*ft_parser_direct(t_list *arg)
{
	t_list	*save;
	int		test;

	save = arg;
	while (arg)
	{
		ft_find_direct(arg);
		test = ft_check_direct(arg);
		if (test == 1)
		{
			ft_putendl_fd("Ambiguous redirection", 2);
			save->error = 1;
		}
		arg = arg->next;
	}
	arg = save;
	return (arg);
}
