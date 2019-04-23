/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   G_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 17:11:20 by koparker          #+#    #+#             */
/*   Updated: 2019/04/23 14:42:53 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_colorized_output_l(t_data *st)
{
	char	*perm;
	char	*name;

	perm = st->l_info->permissions;
	name = st->l_info->file_name;
	if (ft_strnchr(perm, 'w', 8) != NULL)
	{
		if (ft_strrchr(perm, 't') != NULL || ft_strrchr(perm, 'T') != NULL)
			ft_putstr(ft_strjoin(STICKY_BIT_COLOR, name));
		else
			ft_putstr(ft_strjoin(NO_STICKY_BIT_COLOR, name));
	}
	else if (*perm == 'd')
		ft_putstr(ft_strjoin(DIR_COLOR, name));
	else if (*perm == 'b')
		ft_putstr(ft_strjoin(BLOCK_COLOR, name));
	else if (*perm == 'c')
		ft_putstr(ft_strjoin(CHAR_COLOR, name));
	else if (*perm == 'l')
		ft_putstr(ft_strjoin(SIMLNK_BASE_COLOR, name));
	else if (ft_strchr(perm, 'x') != NULL)
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
