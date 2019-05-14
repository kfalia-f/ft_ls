/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:22:10 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/05/14 18:02:56 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_str_path(char *str1, char *str2)
{
	char	*str3;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (str1[0] == '/' && len1 == 1)
		return (ft_strjoin(str1, str2));
	str3 = (char *)malloc(sizeof(char) * (len1 + len2 + 2));
	i = 0;
	while (i < len1)
	{
		str3[i] = str1[i];
		i++;
	}
	str3[i++] = '/';
	j = 0;
	while (i < len1 + len2 + 1)
		str3[i++] = str2[j++];
	str3[i] = '\0';
	return (str3);
}
