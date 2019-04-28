/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colorized.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:57:59 by koparker          #+#    #+#             */
/*   Updated: 2019/04/28 17:12:44 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_print_first_upper_g(char **names, char **perms, size_t row)
{
	struct winsize	w;
	size_t			i;
	size_t			len;

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

void	ft_pr_upper_g(char **names, char **perms, size_t row, size_t max_len)
{
	size_t	i;
	size_t	j;
	size_t	num_of_elems;

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

void	ft_print_simple_colorized(t_data *head)
{
	t_data	*tmp;
	char	**perms;
	size_t	i;
	size_t	list_size;

	i = 0;
	tmp = head;
	list_size = ft_list_size(head);
	if ((perms = ft_memalloc_2d_clean(list_size, PERM_SIZE)) == NULL)
		return ;
	if (!head->perm)
		ft_set_permissions(&head, NULL);
	ft_lstcontent_to_char_arr(perms, head, 1);
	while (tmp)
	{
		ft_colorized_output(perms[i++], tmp->name);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	ft_del(&perms, list_size);
	ft_free_perm(&head);
}
