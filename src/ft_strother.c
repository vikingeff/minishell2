/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:00:11 by gleger            #+#    #+#             */
/*   Updated: 2014/05/18 17:46:13 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	i;
	size_t	j;

	i = ft_strlen(s1) + ft_strlen(s2);
	if (!(r = malloc(sizeof(*r) * (i + 1))))
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		r[i++] = s2[j++];
	r[i] = 0;
	return (r);
}

char		*ft_strdup(const char *s1)
{
	char	*new_str;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	new_str = NULL;
	if (s1)
	{
		while (s1[len])
			len++;
		if (!(new_str = (char*)malloc(sizeof(char) * (len + 1))))
			return (new_str);
		while (i < len)
		{
			new_str[i] = s1[i];
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}

char		*ft_strcpy(char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char		*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char*)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char*)s);
	return (NULL);
}

int			ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	diff;

	i = 0;
	diff = 0;
	while (s1[i] || s2[i])
	{
		diff = s1[i] - s2[i];
		if (diff != 0)
			return (diff);
		i++;
	}
	return (0);
}
