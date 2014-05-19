/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_put.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 18:47:13 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:13:43 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int				puts_write(int c)
{
	write(1, &c, 1);
	return (1);
}

int				term_put(char *opt_id)
{
	if (tputs(tgetstr(opt_id, NULL), 1, puts_write) == ERR)
		return (-1);
	return (0);
}
