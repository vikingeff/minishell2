/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:00:11 by gleger            #+#    #+#             */
/*   Updated: 2014/05/18 17:46:40 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char			*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*r;
	size_t		i;

	if (!s)
		return (NULL);
	if (!(r = malloc(sizeof(*r) * (len + 1))))
		return (NULL);
	i = 0;
	while (len)
	{
		--len;
		r[i] = s[start + i];
		++i;
	}
	r[i] = 0;
	return (r);
}

static int		count_words(const char *str, char c)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static char		*ft_strndup(const char *src, int n)
{
	size_t		i;
	char		*res;

	if (!src)
		return (0);
	if ((res = (char*)malloc(sizeof(char) * (n + 1))) == NULL)
		return (NULL);
	res[n] = 0;
	i = n - 1;
	while (i)
	{
		res[i] = src[i];
		i--;
	}
	res[0] = src[0];
	return (res);
}

static size_t	word_len(const char *str, char c)
{
	size_t		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t		i;
	size_t		j;
	size_t		words;
	size_t		len;
	char		**bat;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	if ((bat = (char**)malloc(sizeof(char*) * (words + 1))) == NULL)
		return (NULL);
	bat[words] = 0;
	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] && s[j] == c)
			j++;
		len = word_len(s + j, c);
		bat[i] = ft_strndup(s + j, len);
		i++;
		j += len;
	}
	return (bat);
}
