/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:00:11 by gleger            #+#    #+#             */
/*   Updated: 2014/05/18 17:45:41 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

void		ft_bzero(void *s, size_t n)
{
	unsigned char	*st;

	st = s;
	while (n > 0)
	{
		st[n - 1] = '\0';
		n--;
	}
}

size_t		ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s != NULL)
	{
		while (s[len])
			len++;
	}
	return (len);
}

int			ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int	nb;
	int	i;
	int	neg;

	i = 0;
	nb = 0;
	neg = 0;
	while (ft_isspace(str[i]) || (str[i] == '-' && ft_isdigit(str[i + 1]))
			|| (str[i] == '+' && ft_isdigit(str[i + 1])))
		i++;
	if (str[i - 1] == '-')
		neg++;
	while (ft_isdigit(str[i]))
	{
		if (ft_isdigit(str[i]) && neg < 3)
		{
			nb = (nb * 10) + (str[i] - '0');
			if (neg == 0)
				neg = 2;
		}
		i++;
	}
	if (neg == 1)
		nb *= -1;
	return (nb);
}
