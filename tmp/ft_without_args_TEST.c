/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_without_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 20:01:59 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/03/27 16:22:10 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char		**ft_lstname_to_str_arr(char **arr, t_data *data)
{
	int		i;
	t_data	*tmp;

	i = 0;
	tmp = data;
	while (tmp != NULL)
	{
		arr[i] = ft_strcpy(arr[i], tmp->name);
		i++;
		tmp = tmp->next;
	}
	return (arr);
}

void		ft_output(char **arr, size_t col, size_t list_size, size_t max_namlen)
{
	size_t	i;
	size_t	row;
	size_t	j;
	size_t	k;
	size_t	c;

	c = max_namlen;
	while ((c + 1) % 8 != 0)
		c++;
	k = 0;
	while (arr[k][0] == '.')
		k++;
	row = (list_size - k) / col + 1;
	if (col % 2 == 0 && row != 2)
		row--;
	j = 0;
	printf("col = %zu, row = %zu\n", col, row);
	while (j < row)
	{
		i = k + j;
		while (i < list_size)
		{
			ft_putstr(arr[i]);
			if (col == 1)
				ft_putchar('\n');
			else
			{
				ft_output_spaces(' ', c - max_namlen);
				ft_putchar('\t');
			}
			i += row;
		}
		if (col != 1)
			ft_putchar('\n');
		j++;
	}
}

static void	ft_window(t_data *data)
{
	struct winsize	w;
	size_t			list_size;
	size_t			max_namlen;
	size_t			col;
	char			**arr;
	size_t			i;

	ioctl(0, TIOCGWINSZ, &w);
	max_namlen = ft_max_namlen(data);
	i = max_namlen;
	while ((i + 1) % 8 != 0)
		i++;
//	printf("%zu\n", (i + 1));
	col = w.ws_col / (i + 1);
//	if (row % 2 == 0)
//		row++;
	list_size = ft_lstsize(data);
	arr = ft_memalloc_2d_clean(list_size, max_namlen);
	arr = ft_lstname_to_str_arr(arr, data);
	ft_output(arr, col, list_size, max_namlen);
}

static void	ft_without_args_true(char *str)
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

void		ft_without_args(char *str)
{
	DIR				*dirp;
	struct dirent	*dp;

	if (TRUE_LS == 1)
	{
		ft_without_args_true(str);
		return ;
	}	
	dirp = opendir(str);
	while ((dp = readdir(dirp)) != NULL)
		ft_putendl(dp->d_name, 0);
	closedir(dirp);
}
