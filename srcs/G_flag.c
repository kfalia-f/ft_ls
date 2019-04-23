/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   G_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 17:11:20 by koparker          #+#    #+#             */
/*   Updated: 2019/04/23 15:15:22 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

size_t	ft_sticky_file_l(t_data *st)
{
	char	*perm;
	char	*name;

	perm = st->l_info->permissions;
	name = st->l_info->file_name;
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

size_t	ft_sticky_dir_l(t_data *st)
{
	char	*perm;
	char	*name;

	perm = st->l_info->permissions;
	name = st->l_info->file_name;
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

void	ft_colorized_output_l(t_data *st)
{
	char	*perm;
	char	*name;

	perm = st->l_info->permissions;
	name = st->l_info->file_name;
	if (ft_sticky_file_l(st))
		ft_putstr(RESET);
	else if (ft_sticky_dir_l(st))
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

void	ft_G_flag_up(t_data **head, t_flags fl)
{
	t_data		*tmp;
	struct stat	buff;

	fl.value = 1;
	tmp = *head;
	(void)buff;	
}
