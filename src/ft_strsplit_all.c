/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleger <gleger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:00:11 by gleger            #+#    #+#             */
/*   Updated: 2014/05/18 11:19:41 by gleger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int		count_words(const char *str)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v')
			i++;
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\v' && str[i])
			count++;
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\v' && str[i])
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
	if ((res = (char *)malloc(sizeof(char) * (n + 1))) == NULL)
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

static size_t	word_len(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\v')
		i++;
	return (i);
}

char			**ft_strsplit_all(char const *s)
{
	size_t		i;
	size_t		j;
	size_t		words;
	size_t		len;
	char		**table;

	if (!s)
		return (NULL);
	words = count_words(s);
	if ((table = (char **)malloc(sizeof(char *) * (words + 1))) == NULL)
		return (NULL);
	table[words] = 0;
	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] && (s[j] == ' ' || s[j] == '\t' || s[j] == '\v'))
			j++;
		len = word_len(s + j);
		table[i] = ft_strndup(s + j, len);
		i++;
		j += len;
	}
	return (table);
}
