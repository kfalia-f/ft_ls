/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:19:19 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/21 15:39:43 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

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

int		ft_corb(t_data *st, int flag)
{
	t_data *tmp;

	tmp = st;
	if (flag == -1)
		return (0);
	while (tmp)
	{
		if (*(tmp->l_info->permissions) == 'c' || *(tmp->l_info->permissions) == 'b')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_size(t_data *tmp, int a[6], int flag)
{
	flag = 0;
	if (*(tmp->l_info->permissions) == 'c' || *(tmp->l_info->permissions) == 'b')
	{
		ft_output_spaces(' ', 1 + a[4] - ft_len(tmp->l_info->maj));
		if (*(tmp->l_info->permissions) == 'c' || *(tmp->l_info->permissions) == 'b')
		{
			ft_putnbr(tmp->l_info->maj);
			ft_putchar(',');
			ft_output_spaces(' ', 1 + a[5] - ft_len(tmp->l_info->min));
			ft_putnbr(tmp->l_info->min);
		}
		else
		{
			ft_output_spaces(' ', 1 + a[5] - ft_len(tmp->l_info->file_size));
			ft_putnbr(tmp->l_info->file_size);
		}
	}
	else
	{
		ft_output_spaces(' ', 2 + a[4] + a[5]);
		ft_putnbr(tmp->l_info->file_size);
	}
}

static int      ft_max_llen(t_data *st, int flag, int f)  //0 = link; 1 = size; 2 = owner; 3 = group 4 = maj 5 = min
{
	t_data  *tmp;
	int     len;
	int     max;

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
		if (f == -1)
			return (max);
		tmp = tmp->next;
	}
	return (max);
}

void	ft_output_info(t_data *st, t_flags fl, int flag)
{
	t_data		*tmp;
	int			a[6];

	tmp = st;
	a[0] = ft_max_llen(st, 0, flag);
	a[1] = ft_max_llen(st, 1, flag);
	a[2] = ft_max_llen(st, 2, flag);
	a[3] = ft_max_llen(st, 3, flag);
	a[4] = ft_max_llen(st, 4, flag);
	a[5] = ft_max_llen(st, 5, flag);
	while (tmp)
	{
		ft_putstr(tmp->l_info->permissions);
		ft_output_spaces(' ', 1 + a[0] - ft_len(tmp->l_info->links));
		ft_putnbr(tmp->l_info->links);
		ft_output_spaces(' ', 1);
		if (!fl.bits.g)
		{
			ft_putstr(tmp->l_info->owner);
			ft_output_spaces(' ', 2 + a[2] - ft_strlen(tmp->l_info->owner));
		}
		ft_putstr(tmp->l_info->group);
		ft_output_spaces(' ', 2 + a[3] - ft_strlen(tmp->l_info->group));
		ft_size(tmp, a, ft_corb(st, flag));
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->l_info->date);
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->l_info->file_name);
		if (tmp->l_info->link)
			ft_putstr(tmp->l_info->link);
		ft_putchar('\n');
		if (flag == -1)
			return ;
		tmp = tmp->next;
	}
}
