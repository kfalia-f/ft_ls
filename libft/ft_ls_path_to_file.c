/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_path_to_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:53:39 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/15 18:57:30 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_ls_path_to_file(char *path, int	flag)
{
	int		i;
	int		len;
	int		k;
	char	*file;
	char	*pt;

	i = 0;
	len = 0;
	while (path[i])
	{
		if (path[i] != '/')
		{
			i++;
			continue ;
		}
		if (path[i] == '/')
			len = i;
		i++;
	}
	if (len == 0 && flag && path[0] != '/')
		return (path);
	k = len + 1;
	len = i - len;
	file = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (path[k])
		file[i++] = path[k++];
	file[i] = '\0';
	i = 0;
	k = ft_strlen(path) - len;
	if (k == 0 && !flag && path[0] != '/')
		return ("./");
	pt = (char *)malloc(sizeof(char) * (k + 2));
	while (i <= k)
	{
		pt[i] = path[i];
		i++;
	}
	pt[i] = '\0';
	if (flag == 1)
		return (file);
	return (pt);
}
