/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/11 15:21:51 by gleger            #+#    #+#             */
/*   Updated: 2014/05/18 11:18:55 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	ft_to_null(t_list *list)
{
	list->next = NULL;
	list->prev = NULL;
	list->mot = NULL;
}

t_list	*ft_lstnew(char *content)
{
	t_list	*newlist;

	if (!(newlist = ft_memalloc(sizeof(*newlist))))
		return (NULL);
	newlist->valeure = NULL;
	if (!content)
		ft_to_null(newlist);
	else
	{
		newlist->next = NULL;
		newlist->prev = NULL;
		newlist->mot = ft_strdup(content);
		newlist->dir = NULL;
		newlist->fd = 0;
		newlist->error = 0;
		newlist->pipenb = 0;
	}
	return (newlist);
}

void	ft_lstadd(t_list **alst, t_list *new)
{
	t_list	*cur;

	if (!alst)
		return ;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	cur = new;
	while (cur->next)
		cur = cur->next;
	cur->next = *alst;
	*alst = new;
}

t_list	*ft_lstadd_first(t_list *lst, t_list *new)
{
	t_list	*save;

	if (lst == NULL)
		return (new);
	save = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	new->prev = lst;
	return (save);
}
