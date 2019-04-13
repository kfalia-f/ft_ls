/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc_2d_clean.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:17:39 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/13 19:38:23 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	**ft_memalloc_2d_clean(size_t str_num, size_t str_size)
{
	char	**s;
	size_t	k;

	if (str_num == 0 || str_size == 0)
		return (NULL);
	k = -1;
	if ((s = (char **)malloc(sizeof(char *) * (str_num + 1))) == NULL)
		return (NULL);
	while (++k < str_num)
		if ((s[k] = (char *)malloc(sizeof(char) * (str_size + 1))) == NULL)
			return (ft_del(&s, k));
	k = 0;
	while (k < str_num)
	{
		ft_bzero(s[k], '\0');
		k++;
	}
	s[str_num] = NULL;
	return (s);
}
