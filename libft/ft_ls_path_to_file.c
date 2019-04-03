/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_path_to_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:53:39 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/03 18:09:58 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_ls_path_to_file(char *path)
{
	int		i;
	int		len;
	int		k;
	char	*file;

	i = 0;
	while (path[i])
	{
		while (path[i] && path[i] != '/')
			i++;
		if (path[i] == '/')
			len = i;
		i++;
	}
	k = len + 1;
	len = i - len;
	file = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (path[k])
		file[i++] = path[k++];
	file[i] = '\0';
	return (file);
}
