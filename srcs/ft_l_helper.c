/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <kfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:26:06 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/27 16:04:04 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_total(char *path_name, t_data *st)
{
	struct stat buff;
	t_data		*tmp;
	int			total;
	char		*pt;

	tmp = st;
	total = 0;
	ft_putstr("total ");
	while (tmp)
	{
		pt = ft_str_path(path_name, tmp->name);
		lstat(pt, &buff);
		free(pt);
		total += buff.st_blocks;
		tmp = tmp->next;
	}
	ft_putnbr(total);
	ft_putchar('\n');
}

void	time_balanser_get_info(t_data *st, t_flags fl, struct stat buff)
{
	if (fl.bits.upper_u)
	{
		st->l_info->date = ft_date(ctime(&buff.st_birthtime)
			, buff.st_birthtime, 0, 0);
		st->time = buff.st_birthtime;
	}
	else if (fl.bits.u)
	{
		st->l_info->date = ft_date(ctime(&buff.st_atime), buff.st_atime, 0, 0);
		st->time = buff.st_atime;
	}
	else
	{
		st->l_info->date = ft_date(ctime(&buff.st_mtime), buff.st_mtime, 0, 0);
		st->time = buff.st_mtime;
	}
}

void	ft_l(char *path_name, t_flags fl)
{
	DIR				*dirp;
	t_data			*lhead;
	t_data			*lnode;
	char			*pt;

	if (!(dirp = opendir(path_name)))
		return ;
	lhead = ft_readdir(dirp, fl);
	lnode = lhead;
	while (lnode)
	{
		new_l_node(&lnode, lnode->name, fl);
		pt = ft_str_path(path_name, lnode->name);
		get_info(pt, lnode, fl);
		free(pt);
		lnode = lnode->next;
	}
	ft_balanser_sort(&lhead, fl, NULL);
	if (lhead)
		ft_total(path_name, lhead);
	ft_output_info(lhead, fl);
	closedir(dirp);
	ft_free_list(&lhead, 1);
}

void		ft_arr(t_data *st, int a[6])
{
	a[0] = ft_max_llen(st, 0);
	a[1] = ft_max_llen(st, 1);
	a[2] = ft_max_llen(st, 2);
	a[3] = ft_max_llen(st, 3);
	a[4] = ft_max_llen(st, 4);
	a[5] = ft_max_llen(st, 5);
}
