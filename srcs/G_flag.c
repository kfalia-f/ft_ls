/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   G_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:48:00 by koparker          #+#    #+#             */
/*   Updated: 2019/04/26 16:53:58 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

size_t  ft_sticky_file(char *perm, char *name)
{
	char	*tmp;

	tmp = NULL;
	if (*perm == '-')
	{
		if (ft_strrchr(perm, 't') || ft_strchr(perm, 'x'))
		{
			if (ft_strnchr(perm, 's', 3) || ft_strnchr(perm, 'S', 3))
				tmp = ft_strjoin(EXE_SETUID_COLOR, name);
			else if (ft_strnchr(perm, 's', 6) || ft_strnchr(perm, 'S', 6))
				tmp = ft_strjoin(EXE_SETGID_COLOR, name);
			else
				tmp = ft_strjoin(EXE_COLOR, name);
			ft_putstr(tmp);
			ft_strdel(&tmp);
			return (1);
		}
	}
	return (0);
}

size_t  ft_sticky_dir(char *perm, char *name)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strnchr(perm, 'w', 8) && *perm == 'd')
	{
		if (ft_strrchr(perm, 't') || ft_strrchr(perm, 'T'))
			tmp = ft_strjoin(STICKY_BIT_COLOR, name);
		else
			tmp = ft_strjoin(NO_STICKY_BIT_COLOR, name);
		ft_putstr(tmp);
		ft_strdel(&tmp);
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
	char	*tmp;

	tmp = NULL;
	if (ft_sticky_file(perm, name))
		ft_putstr(RESET);
	else if (ft_sticky_dir(perm, name))
		ft_putstr(RESET);
	else if (*perm == 'd')
		tmp = ft_strjoin(DIR_COLOR, name);
	else if (*perm == 'b')
		tmp = ft_strjoin(BLOCK_COLOR, name);
	else if (*perm == 'c')
		tmp = ft_strjoin(CHAR_COLOR, name);
	else if (*perm == 'l')
		tmp = ft_strjoin(SIMLNK_BASE_COLOR, name);
	else if (ft_strchr(perm, 'x'))
		tmp = ft_strjoin(EXE_COLOR, name);
	else
		ft_putstr(name);
	if (tmp)
	{
		ft_putstr(tmp);
		ft_strdel(&tmp);
	}
	ft_putstr(RESET);
}
