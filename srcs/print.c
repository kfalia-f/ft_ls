/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <kfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:08:44 by koparker          #+#    #+#             */
/*   Updated: 2019/04/28 16:19:47 by kfalia-f         ###   ########.fr       */
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
			ft_output_spaces(' ', max_len - ft_strlen(names[j]));
			ft_putchar('\t');
			j += row;
		}
		ft_putchar('\n');
		i++;
	}
}

void	ft_print_contents(char **names, char **perms, size_t max_len,
						t_flags fl)
{
	struct winsize	w;
	size_t			row;
	size_t			len;
	size_t			col;
	size_t			n_of_elems;

	ioctl(0, TIOCGWINSZ, &w);
	len = max_len;
	n_of_elems = ft_2d_strlen(names);
	if (fl.bits.upper_g)
	{
		(col = (size_t)w.ws_col / (len + 1)) == 0 ? (col++) : col;
		((row = n_of_elems / col) && (n_of_elems % col == 0)) ? row : (row++);
		col == 1 ? ft_print_first_upper_g(names, perms, row)
			: ft_pr_upper_g(names, perms, row, max_len);
	}
	else
	{
		while ((len + 1) % 8 != 0)
			len++;
		(col = (size_t)w.ws_col / (len + 1)) == 0 ? (col++) : col;
		((row = n_of_elems / col) && (n_of_elems % col == 0)) ? row : (row++);
		(col == 1) ? ft_print_first(names, w, row)
			: ft_pr(names, max_len, row, n_of_elems);
	}
}

void	ft_print_simple(t_data *head, t_flags fl)
{
	t_data	*tmp;

	tmp = NULL;
	if (head == NULL)
		return ;
	if (fl.bits.upper_g)
		ft_print_simple_colorized(head);
	else
	{
		tmp = head;
		while (tmp)
		{
			ft_putendl(tmp->name, 0);
			tmp = tmp->next;
		}
	}
}

void	ft_print(t_data *head, t_flags fl, char *path)
{
	char	**names;
	char	**perms;
	size_t	max_len;
	size_t	list_size;

	list_size = ft_list_size(head);
	max_len = ft_max_namlen(head);
	if ((names = ft_memalloc_2d_clean(list_size, max_len)) == NULL)
		return ;
	ft_lstcontent_to_char_arr(names, head, 0);
	perms = NULL;
	if (fl.bits.upper_g)
	{
		if ((perms = ft_memalloc_2d_clean(list_size, PERM_SIZE)) == NULL)
			return ;
		if (!head->perm)
			ft_set_permissions(&head, path);
		ft_lstcontent_to_char_arr(perms, head, 1);
	}
	ft_print_contents(names, perms, max_len, fl);
	ft_del(&names, list_size);
	if (fl.bits.upper_g)
	{
		ft_del(&perms, list_size);
		ft_free_perm(&head);
	}
}
