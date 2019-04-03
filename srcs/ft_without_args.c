/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_without_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 20:01:59 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/02 17:47:51 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

// doesn't work properly with some cols and row.
// Also need to row<->col in naming
void		ft_output(char **arr, size_t row, size_t list_size, size_t max_namlen)
{
	size_t	i;
	size_t	col;
	size_t	j;
	size_t	k;

	k = 0;
	while (arr[k][0] == '.')
		k++;
	col = (list_size - k) / row + 1;
	j = 0;
	while (j < col)
	{
		i = k + j;
		while (i < list_size)
		{
			ft_putstr(arr[i]);
			ft_output_spaces(' ', max_namlen - ft_strlen(arr[i]) + 1);
			ft_putchar('\t');
			i += col;
		}
		ft_putchar('\n');
		j++;
	}
}

//some problem may lay here. look at ../tmp/ft_without_args_TEST.c
void	ft_window(t_data *data)
{
	struct winsize	w;
	size_t			list_size;
	size_t			max_namlen;
	size_t			row;
	char			**arr;

	ioctl(0, TIOCGWINSZ, &w);
	max_namlen = ft_max_namlen(data);
	row = w.ws_col / (max_namlen + TAB + 1);
	list_size = ft_list_size(data);
	arr = ft_memalloc_2d_clean(list_size, max_namlen);
	arr = ft_lstname_to_char_arr(arr, data);
	ft_output(arr, row, list_size, max_namlen);
}

void	ft_without_args(char *str)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_data			*head;
	t_data			*node;

	head = NULL;
	dirp = opendir(str);
	while ((dp = readdir(dirp)) != NULL)
	{
		node = new_node(dp);
		push_back(&head, node);
	}
	closedir(dirp);
	node = ft_ascii_sort(&head);
	ft_window(node);
}
