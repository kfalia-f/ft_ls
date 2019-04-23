/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colorized.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:57:59 by koparker          #+#    #+#             */
/*   Updated: 2019/04/23 17:23:58 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void    ft_print_first_upper_g(char **names, size_t row, t_data *head, t_flags fl)
{
	struct winsize  w;
	size_t          i;
	size_t          len;

	i = 0;
	ioctl(0, TIOCGWINSZ, &w);
	while (i < row)
	{
		if (fl.bits.upper_g)
			ft_colorized_output(head);
		else
			ft_putstr(names[i]);
		len = ft_strlen(names[i]);
		if (len <= (size_t)w.ws_col)
			ft_output_spaces(' ', (size_t)w.ws_col - len);
		if (i + 1 == row)
			break ;
		ft_putchar('\n');
		i++;
	}
}

void    ft_pr_upper_g(char **names, size_t row, t_data *head, t_flags fl)
{
	size_t  i;
	size_t  j;
	size_t  num_of_elems;
	size_t  max_len;

	i = 0;
	num_of_elems = ft_2d_strlen(names);
	max_len = ft_max_namlen(head);
	while (i < row)
	{
		j = i;
		while (j < num_of_elems)
		{
			if (fl.bits.upper_g)
			{
				ft_colorized_output(head);
				ft_output_spaces(' ', max_len - ft_strlen(names[j]));
			}
			else
			{
				ft_putstr(names[j]);
				ft_output_spaces(' ', max_len - ft_strlen(names[j]));
				ft_putchar('\t');
			}
			j += row;
		}
		ft_putchar('\n');
		i++;
	}
}
