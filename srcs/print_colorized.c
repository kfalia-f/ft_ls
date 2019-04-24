/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colorized.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:57:59 by koparker          #+#    #+#             */
/*   Updated: 2019/04/24 16:55:13 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void    ft_print_first_upper_g(char **names, char **perms, size_t row)
{
	struct winsize  w;
	size_t          i;
	size_t          len;

	i = 0;
	ioctl(0, TIOCGWINSZ, &w);
	while (i < row)
	{
		ft_colorized_output(perms[i], names[i]);
		len = ft_strlen(names[i]);
		if (len <= (size_t)w.ws_col)
			ft_output_spaces(' ', (size_t)w.ws_col - len);
		ft_putchar('\n');
		i++;
	}
}

void    ft_pr_upper_g(char **names, char **perms, size_t row, size_t max_len)
{
	size_t  i;
	size_t  j;
	size_t  num_of_elems;

	i = 0;
	num_of_elems = ft_2d_strlen(names);
	while (i < row)
	{
		j = i;
		while (j < num_of_elems)
		{
			ft_colorized_output(perms[j], names[j]);
			ft_output_spaces(' ', max_len + 1 - ft_strlen(names[j]));
			j += row;
		}
		ft_putchar('\n');
		i++;
	}
}
