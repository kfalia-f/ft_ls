/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:26:06 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/21 18:16:38 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int     ft_total(char *path_name, t_data *st)
{
	struct stat buff;
	t_data      *tmp;
	int         total;

	tmp = st;
	total = 0;
	while (tmp)
	{
		stat(ft_str_path(path_name, tmp->name), &buff);
		total += buff.st_blocks;
		tmp = tmp->next;
	}
	return (total);
}

void    time_balanser_get_info(t_data *st, t_flags fl, struct stat buff)
{
	if (fl.bits.upper_u)
	{
		st->l_info->date = ft_date(ctime(&buff.st_birthtime), buff.st_birthtime);
		st->time = buff.st_birthtime;
	}
	else if (fl.bits.u)
	{
		st->l_info->date = ft_date(ctime(&buff.st_atime), buff.st_atime);
		st->time = buff.st_atime;
	}
	else
	{
		st->l_info->date = ft_date(ctime(&buff.st_mtime), buff.st_mtime);
		st->time = buff.st_mtime;
	}
}

void    ft_l(char *path_name, t_flags flags)
{
	DIR             *dirp;
	struct dirent   *dp;
	t_data          *lhead;
	t_data          *lnode;

	lhead = NULL;
	if (!(dirp = opendir(path_name)))
		return ;
	while ((dp = readdir(dirp)) != NULL)
	{
		if (*(dp->d_name) == '.')
			if (flags.bits.a == 0 && flags.bits.f == 0)
				continue ;
		lnode = new_node(dp);
		push_back(&lhead, lnode);
	}
	/*  if (lhead)
	 *      //  ft_balanser_sort(&lhead, flags, path_name);
	 *          */  lnode = lhead;
	while (lnode)
	{
		new_l_node(&lnode, lnode->name, flags);
		get_info(ft_str_path(path_name, lnode->name), lnode, flags);
		lnode = lnode->next;
	}
	ft_balanser_sort(&lhead, flags, NULL);
	if (lhead)
	{
		ft_putstr("total ");
		ft_putnbr(ft_total(path_name, lhead));
		ft_putchar('\n');
	}
	ft_output_info(lhead, flags, 0);
	//ft_free_list(lhead);
	//}
}
