/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recurcion_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 20:04:59 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/07 21:40:04 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		ft_files(t_data *head)
{
	struct stat		buff;
	t_data			*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		stat(tmp->name, &buff);
		if (S_ISDIR(buff.st_mode))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_recurs(char *path_name, t_flags flags)
{
	DIR				*dirp;
	struct dirent	*dp;
	struct stat		buff;
	t_data			*head;
	t_data			*node;

	head = NULL;
	if (!(dirp = opendir(path_name)))
		return ;
	while ((dp = readdir(dirp)) != NULL)
	{
		if (*(dp->d_name) == '.')
			continue ;
		node = new_node(dp);
		push_back(&head, node);
	}
	closedir(dirp);
	node = head;
	if (ft_files(head) == 1)
	{
		ft_print(head, flags);
		ft_free_list(node);
		return ;
	}
	if (head != NULL)
		ft_print(ft_ascii_sort(&head), flags);
	while (head != NULL)
	{
		if ((stat(head->name, &buff) >= 0))
			if (S_ISDIR(buff.st_mode))
			{
				ft_putendl(ft_str_path(path_name, head->name), 2);
				ft_recurs(ft_str_path(path_name, head->name), flags);
			}
		head = head->next;
	}
	ft_free_list(node);
	return ;
}

void	ft_recurcion_flag(char **av, int flag, t_flags flags)
{
	struct stat		buff;
	int				i;

	i = 0;
	if (flag == 0)
	{
		ft_recurs(".", flags);
		return ;
	}
	while (av[i])
	{
		stat(av[i], &buff);
		if (!(S_ISDIR(buff.st_mode)))
		{
			i++;
			continue ;
		}
		ft_putendl(av[i], 1);
		ft_recurs(av[i], flags);
		if (flag - i >= 0)
			ft_putchar('\n');
		i++;
	}
}
