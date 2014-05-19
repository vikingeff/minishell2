/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 09:23:32 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:25:19 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		term_set_attr(t_term *term)
{
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (term_error(3));
	return (0);
}

int		term_canonical_mode(t_env *env, int mode)
{
	if (mode == 0)
		env->term->c_lflag &= ~(ICANON | ECHO);
	else
		env->term->c_lflag = env->canon_save;
	if (term_set_attr(env->term))
		return (-1);
	return (0);
}

void	term_edit_set(t_env *env)
{
	env->term_len = tgetnum("co");
	term_put("vi");
	term_put("im");
	term_canonical_mode(env, 0);
}

int		term_ini(t_env *env)
{
	char	*n_term;

	if ((n_term = env_get_value("TERM", env)) == NULL)
		return (term_error(0));
	if (tgetent(NULL, n_term) == -1)
		return (term_error(1));
	if (tcgetattr(0, env->term) == -1)
		return (term_error(2));
	env->canon_save = env->term->c_lflag;
	return (0);
}

void	term_std_set(t_env *env)
{
	term_put("ei");
	term_put("ve");
	term_canonical_mode(env, 1);
}
