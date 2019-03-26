/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_without_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 20:01:59 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/03/26 16:16:17 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
**Need to rework
*/

// TODO: need to know the window size to make real columns
static void	ft_output(t_data *data)
{
	struct winsize	w;
	t_data			*tmp;
	int				max_namlen;

	ioctl(0, TIOCGWINSZ, &w);
	tmp = data;
	max_namlen = ft_max_namlen(tmp);
	while (tmp->next)
	{
		while ((*tmp->name) == '.')
		{
			tmp = tmp->next;
			continue ;
		}
		ft_putstr(tmp->name);
		ft_output_spaces(' ', max_namlen - tmp->len + 1);
		ft_putchar('\t');
		tmp = tmp->next;
	}
	ft_putendl(tmp->name, 0);
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
	ft_output(node);
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
