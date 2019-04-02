/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:08:44 by koparker          #+#    #+#             */
/*   Updated: 2019/04/02 21:30:53 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_print_contents(char **names, size_t max_len, size_t col)
{
	struct winsize w;
	size_t	row;
	size_t	num_of_elems;
	size_t	j;
	size_t	i;

/*	if (fl->bits.a != 0 || fl->bits.f != 0)
	{
		while ((*tmp->name) == '.')
			tmp = tmp->next;
	}*/
	ioctl(0, TIOCGWINSZ, &w);
	num_of_elems = ft_2d_strlen(names);
	((row = num_of_elems / col) && (num_of_elems % col == 0)) ? row : (row = row + 1);
//	printf("row %zu col %zu\n", row, col);
	j = 0;
	while (j < row)
	{
		i = j;
		while (i < num_of_elems)
		{
			ft_putstr(names[i]);
			if (col == 1 && ft_strlen(names[i]) <= w.ws_col)
			{
				ft_output_spaces(' ', w.ws_col - ft_strlen(names[i]));
			}
			else
				ft_output_spaces(' ', max_len - ft_strlen(names[i]) + 1);
			if (col == 1 && j + 1 == row)
			{
	//			printf("j + 1 == %zu\n", j + 1);
				//ij++;
				break ;
			}
			if (col != 1)
				ft_putchar('\t');
			i += row;
		}
	//	else
			ft_putchar('\n');
		j++;
	}
}

void	ft_print(t_data	*head)
{
	struct winsize	w;
	char			**names;
	size_t			len;
	size_t			max_len;
	size_t			col;

	ioctl(0, TIOCGWINSZ, &w);
	max_len = ft_max_namlen(head);
	names = ft_memalloc_2d_clean(ft_list_size(head), max_len);
	names = ft_lstname_to_char_arr(names, head);
	len = max_len;
	while ((len + 1) % 8 != 0)
		len++;
	(col = w.ws_col / (len + 1)) == 0 ? col = 1 : col;
	ft_print_contents(names, max_len, col);
}
