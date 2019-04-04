/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:08:44 by koparker          #+#    #+#             */
/*   Updated: 2019/04/04 15:53:28 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_print_first(char **names, struct winsize w, size_t row)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (i < row)
	{
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

void	ft_pr(char **names, size_t max_len, size_t row, size_t num_of_elems)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < row)
	{
		j = i;
		while (j < num_of_elems)
		{
			ft_putstr(names[j]);
			ft_output_spaces(' ', max_len - ft_strlen(names[j]) + 1);
			ft_putchar('\t');
			j += row;
		}
		ft_putchar('\n');
		i++;
	}
}

void	ft_print_contents(char **names, size_t max_len)
{
	struct winsize	w;
	size_t			row;
	size_t			len;
	size_t			col;
	size_t			num_of_elems;

	ioctl(0, TIOCGWINSZ, &w);
	len = max_len;
	while ((len + 1) % 8 != 0)
		len++;
	(col = (size_t)w.ws_col / (len + 1)) == 0 ? (col++) : col;
	num_of_elems = ft_2d_strlen(names);
	((row = num_of_elems / col) && (num_of_elems % col == 0)) ? row : (row++);
	if (col == 1)
		ft_print_first(names, w, row);
	else
		ft_pr(names, max_len, row, num_of_elems);
}

void	ft_print(t_data *head, t_flags fl)
{
	char	**names;
	size_t	max_len;

	if (fl.bits.a == 0 || fl.bits.f == 0)
	{
		while ((*head->name) == '.')
			head = head->next;
	}
	max_len = ft_max_namlen(head);
	names = ft_memalloc_2d_clean(ft_list_size(head), max_len);
	names = ft_lstname_to_char_arr(names, head);
	ft_print_contents(names, max_len);
}

void	ft_print_without_args(t_data *head)
{
	t_flags			fl;
	char			**names;
	size_t			max_len;

	fl.value = 0;
	while ((*head->name) == '.')
		head = head->next;
	max_len = ft_max_namlen(head);
	names = ft_memalloc_2d_clean(ft_list_size(head), max_len);
	names = ft_lstname_to_char_arr(names, head);
	ft_print_contents(names, max_len);
}
