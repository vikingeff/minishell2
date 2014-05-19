/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 12:30:18 by gleger            #+#    #+#             */
/*   Updated: 2014/05/13 12:14:59 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}

void	ft_putnbr(int n)
{
	char	*str;

	str = "-2147483648";
	if (n != -2147483648)
	{
		if (n < 0)
		{
			ft_putchar('-');
			n *= -1;
		}
		if (n > 9)
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
		if (n < 10)
			ft_putchar('0' + n);
	}
	else
		ft_putstr(str);
}

void	ft_putendl(char const *s)
{
	ft_putstr(s);
	ft_putchar('\n');
}
