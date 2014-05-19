/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 16:34:51 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:16:04 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static t_list	*ft_fill_arg_logical(char *str, t_list *arg,
	int index, int start)
{
	char	*tmp;
	char	buf[3];

	buf[0] = str[index];
	buf[1] = str[index];
	buf[2] = 0;
	tmp = ft_strsub(str, start, index - start);
	arg = ft_add_arg(tmp, buf, arg);
	free(tmp);
	return (arg);
}

static t_list	*ft_fill_arg_separator(char *str, t_list *arg,
	int index, int start)
{
	char	*tmp;
	char	buf[2];

	buf[0] = str[index];
	buf[1] = 0;
	tmp = ft_strsub(str, start, index - start);
	arg = ft_add_arg(tmp, buf, arg);
	free(tmp);
	return (arg);
}

static t_list	*ft_fill_last(char *str, t_list *arg, int index, int start)
{
	char	*tmp;

	tmp = ft_strsub(str, start, index - start);
	arg = ft_add_arg(tmp, ";", arg);
	if (tmp)
		free(tmp);
	return (arg);
}

static t_list	*ft_while_parser(char *str, int index, int start, t_list *arg)
{
	while (str[index])
	{
		if ((str[index] == '&' && str[index + 1] == '&')
			|| (str[index] == '|' && str[index + 1] == '|'))
		{
			arg = ft_fill_arg_logical(str, arg, index, start);
			start = index + 2;
			index++;
		}
		else if (str[index] == ';' || str[index] == '|')
		{
			arg = ft_fill_arg_separator(str, arg, index, start);
			start = index + 1;
		}
		index++;
	}
	arg = ft_fill_last(str, arg, index, start);
	arg = ft_parser_direct(arg);
	return (arg);
}

t_list			*ft_parser(char *str)
{
	t_list	*arg;
	int		index;
	int		start;

	index = 0;
	start = 0;
	arg = NULL;
	arg = ft_while_parser(str, index, start, arg);
	if (ft_parse_arg(arg))
	{
		ft_free_arg(&arg);
		return (NULL);
	}
	return (arg);
}
