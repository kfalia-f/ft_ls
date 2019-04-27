/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <kfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:19:19 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/27 16:07:13 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int			ft_len(size_t n)
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

int			ft_corb(t_data *st)
{
	t_data *tmp;

	tmp = st;
	while (tmp)
	{
		if (*(tmp->l_info->perm) == 'c' ||
				*(tmp->l_info->perm) == 'b')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		ft_size(t_data *tmp, int a[6], int flag)
{
	if (*(tmp->l_info->perm) == 'c' || *(tmp->l_info->perm) == 'b')
	{
		ft_output_spaces(' ', 1 + a[4] - ft_len(tmp->l_info->maj));
		if (*(tmp->l_info->perm) == 'c' || *(tmp->l_info->perm) == 'b')
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
		if (flag)
			ft_output_spaces(' ', 2 + a[4] + a[5]);
		else
			ft_output_spaces(' ', a[1] - ft_len(tmp->l_info->file_size));
		ft_putnbr(tmp->l_info->file_size);
	}
}

int			ft_max_llen(t_data *st, int flag)
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

void		ft_output_info(t_data *st, t_flags fl)
{
	t_data		*tmp;
	int			a[6];

	tmp = st;
	ft_arr(st, a);
	while (tmp)
	{
		ft_putstr(tmp->l_info->perm);
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
		ft_size(tmp, a, ft_corb(st));
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->l_info->date);
		ft_output_spaces(' ', 1);
		if (fl.bits.upper_g)
			ft_colorized_output_l(tmp);
		else
			ft_putstr(tmp->l_info->file_name);
		if (tmp->l_info->link)
			ft_putstr(tmp->l_info->link);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}
