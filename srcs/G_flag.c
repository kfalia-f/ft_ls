/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   G_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:48:00 by koparker          #+#    #+#             */
/*   Updated: 2019/04/25 13:55:43 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

size_t  ft_sticky_file(char *perm, char *name)
{
	if (*perm == '-')
	{
		if (ft_strrchr(perm, 't') || ft_strchr(perm, 'x'))
		{
			if (ft_strnchr(perm, 's', 3) || ft_strnchr(perm, 'S', 3))
				ft_putstr(ft_strjoin(EXE_SETUID_COLOR, name));
			else if (ft_strnchr(perm, 's', 6) || ft_strnchr(perm, 'S', 6))
				ft_putstr(ft_strjoin(EXE_SETGID_COLOR, name));
			else
				ft_putstr(ft_strjoin(EXE_COLOR, name));
			return (1);
		}
	}
	return (0);
}

size_t  ft_sticky_dir(char *perm, char *name)
{
	if (ft_strnchr(perm, 'w', 8) && *perm == 'd')
	{
		if (ft_strrchr(perm, 't') || ft_strrchr(perm, 'T'))
			ft_putstr(ft_strjoin(STICKY_BIT_COLOR, name));
		else
			ft_putstr(ft_strjoin(NO_STICKY_BIT_COLOR, name));
		return (1);
	}
	return (0);
}

void    ft_set_permissions(t_data **head, char *path)
{
	struct stat buff;
	t_data      *tmp;
	char 		*path_name;

	tmp = *head;
	while (tmp)
	{
		if (path)
			path_name = ft_str_path(path, tmp->name);
		else
			path_name = tmp->name;
		lstat(path_name, &buff);
		tmp->perm = get_permission(buff.st_mode, path_name);
		tmp = tmp->next;
	}
}

void    ft_colorized_output(char *perm, char *name)
{
	if (ft_sticky_file(perm, name))
		ft_putstr(RESET);
	else if (ft_sticky_dir(perm, name))
		ft_putstr(RESET);
	else if (*perm == 'd')
		ft_putstr(ft_strjoin(DIR_COLOR, name));
	else if (*perm == 'b')
		ft_putstr(ft_strjoin(BLOCK_COLOR, name));
	else if (*perm == 'c')
		ft_putstr(ft_strjoin(CHAR_COLOR, name));
	else if (*perm == 'l')
		ft_putstr(ft_strjoin(SIMLNK_BASE_COLOR, name));
	else if (ft_strchr(perm, 'x'))
		ft_putstr(ft_strjoin(EXE_COLOR, name));
	else
		ft_putstr(name);
	ft_putstr(RESET);
}
