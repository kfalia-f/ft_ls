/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recurcion_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 20:04:59 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/04 15:48:14 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_output_r(t_data *head)
{
	while (head != NULL)
	{
		if (*(head->name) == '.')
		{
			head = head->next;
			continue ;
		}
		ft_putstr(head->name);
		ft_putchar('\t');
		head = head->next;
	}
	ft_putchar('\n');
}

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
}

void	ft_recurcion_flag(char **av, int i, int flag, t_flags flags)
{
	struct stat		buff;

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