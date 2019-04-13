/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 20:52:16 by koparker          #+#    #+#             */
/*   Updated: 2019/04/13 19:39:55 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_words_len(char const *s, char c)
{
	size_t		res;
	const char	*tmp;

	res = 0;
	tmp = s;
	while (*tmp)
	{
		while (*tmp == c)
			tmp++;
		if (*tmp)
			res++;
		while (*tmp && *tmp != c)
			tmp++;
	}
	return (res);
}

static char		*ft_strncpy_custom(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char			**ft_strsplit(char const *s, char c)
{
	const char	*word_head;
	size_t		k;
	char		**res;

	if (s == NULL || c == 0)
		return (NULL);
	if (!(res = (char **)malloc(sizeof(char*) * (ft_words_len(s, c) + 1))))
		return (NULL);
	k = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		word_head = s;
		while (*s && *s != c)
			s++;
		if (!(res[k] = ft_memalloc(s - word_head + 1)))
			ft_del(&res, k);
		else if ((s - word_head) != 0)
			ft_strncpy_custom(res[k++], word_head, s - word_head);
	}
	res[k] = NULL;
	return (res);
}
