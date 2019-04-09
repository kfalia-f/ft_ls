/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursion_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:32:11 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/09 16:34:30 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		ft_only_files(t_data *head)
{
	struct stat		buff;
	t_data			*tmp;

	tmp = head;
	while (tmp)
	{
		if (*(tmp->name) == '.')
		{
			tmp = tmp->next;
			continue ;
		}
		stat(tmp->name, &buff);
	   	if (S_ISDIR(buff.st_mode))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_recurs(char *path_name, DIR *dirp, t_flags fl)
{
	DIR				*dirp2;
	t_data			*head;
	t_data			*tmp;
	char			*path;

	ft_putendl(path_name, 1);
	head = ft_readdir(dirp);
	if (ft_only_files(head))
	{
		ft_print(head, fl);
		ft_putchar('\n');
		ft_free_list(head);
		return ;
	}
	tmp = head;
	if (tmp)
	{
		ft_print(head, fl);
		ft_putchar('\n');
	}
	while (tmp)
	{
		if (*(tmp->name) == '.')
		{
			tmp = tmp->next;
			continue ;
		}
		path = ft_str_path(path_name, tmp->name);
		if ((dirp2 = opendir(path)))
		{
			ft_recurs(path, dirp2, fl);
			closedir(dirp2);
		}
		tmp = tmp->next;
	}
	ft_free_list(head);
}

void	ft_recursion_flag(char **av, int flag, t_flags fl)
{
	DIR			*dirp;
	int			i;

	i = 0;
	if (flag == 0)
	{
		dirp = opendir(".");
		ft_recurs(".", dirp, fl);
		return ;
	}
	while (av[i])
	{
		if ((dirp = opendir(av[i])))
		{
			ft_recurs(av[i], dirp, fl);
			closedir(dirp);
			ft_putchar('\n');
		}
		i++;
	}
}
