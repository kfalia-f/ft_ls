/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc_2d_clean.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:17:39 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/03/26 19:22:39 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_del(char ***a, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free((*a)[i]);
		(*a)[i] = NULL;
		i++;
	}
	free(*a);
	*a = NULL;
	return (NULL);
}

char	**ft_memalloc_2d_clean(size_t i, size_t j)
{
	char	**s;
	size_t	k;

	k = -1;
	if ((s = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		return (NULL);
	while (++k < i)
		if ((s[k] = (char *)malloc(sizeof(char) * (j + 1))) == NULL)
			return (ft_del(&s, k));
	k = 0;
	while (k < i)
	{
		ft_bzero(s[k], '\0');
		k++;
	}
	s[i] = NULL;
	return (s);
}
