/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_path_to_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <kfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:53:39 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/28 17:40:24 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_path(char *path, int len)
{
	char	*res;
	int		i;
	int		k;

	i = 0;
	k = ft_strlen(path) - len;
	if (k == 0 && path[0] != '/')
		return ("./");
	res = (char *)malloc(sizeof(char) * (k + 2));
	while (i <= k)
	{
		res[i] = path[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_pt(char *path, int flag, int len, int i)
{
	int		k;
	char	*file;

	while (path[++i])
	{
		if (path[i] != '/')
			continue ;
		if (path[i] == '/')
			len = i;
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
	if (flag == 1)
		return (file);
	free(file);
	return (ft_path(path, len));
}

char	*ft_ls_path_to_file(char *path, int flag)
{
	return (ft_pt(path, flag, 0, -1));
}
