/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_edit_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 00:47:42 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:13:44 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	term_edit_set(t_env *env)
{
	env->term_len = tgetnum("co");
	term_put("vi");
	term_put("im");
	term_canonical_mode(env, 0);
}
