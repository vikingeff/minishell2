/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 18:26:37 by gleger            #+#    #+#             */
/*   Updated: 2014/03/27 09:16:57 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	ft_free_tab(char **table)
{
	int	index;

	index = 0;
	while (table[index])
	{
		free(table[index]);
		index++;
	}
	free(table);
}

void	ft_dup2(int newfd, int oldfd)
{
	if (dup2(newfd, oldfd) == -1)
		ft_putstr("Dup2 Error\n");
}

t_list	*ft_add_arg(char *str, char *type, t_list *list)
{
	t_list	*save;

	list = ft_lstadd_first(list, ft_lstnew(str));
	save = list;
	while (list->next)
		list = list->next;
	list->valeure = ft_strdup(type);
	list = save;
	return (list);
}

void	ft_close(int fd[2])
{
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1 && fd[1] != 0)
		close(fd[1]);
}

char	**ft_tab_dup(char **table)
{
	char	**newtab;
	int		index;
	int		size;

	size = ft_tablen(table);
	index = 0;
	if (!(newtab = (char**)malloc(sizeof(char*) * size)))
		return (NULL);
	while (index < size)
	{
		newtab[index] = ft_strdup(table[index]);
		index++;
	}
	newtab[index] = NULL;
	return (newtab);
}
