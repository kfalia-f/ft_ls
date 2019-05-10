/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <kfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:26:06 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/05/10 18:24:13 by kfalia-f         ###   ########.fr       */
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
	DIR		*dirp;
	t_data	*lhead;
	t_data	*lnode;
	char	*pt;

	if (!(dirp = opendir(path_name)))
		return ;
	lhead = ft_readdir(dirp, path_name, fl);
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

int		ft_len(size_t n)
{
	int size;

	size = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

int		ft_max_llen(t_data *st, int flag)
{
	t_data	*tmp;
	int		len;
	int		max;

	tmp = st;
	max = 0;
	while (tmp)
	{
		if (flag == 0)
			len = ft_len(tmp->l_info->links);
		else if (flag == 1)
			len = ft_len(tmp->l_info->file_size);
		else if (flag == 2)
			len = ft_strlen(tmp->l_info->owner);
		else if (flag == 3)
			len = ft_strlen(tmp->l_info->group);
		else if (flag == 4)
			len = ft_len(tmp->l_info->maj);
		else if (flag == 5)
			len = ft_len(tmp->l_info->min);
		if (max < len)
			max = len;
		tmp = tmp->next;
	}
	return (max);
}
