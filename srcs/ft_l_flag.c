/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:24:27 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/03 18:16:08 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	get_file_type(mode_t st_mode)
{
	if (S_ISLNK(st_mode))
		ft_putchar('l');
	else if (S_ISREG(st_mode))
		ft_putchar('-');
	else if (S_ISDIR(st_mode))
		ft_putchar('d');
}

void	get_permission(mode_t st_mode)
{
	char 		c;

	ft_putchar((c = st_mode & S_IRUSR ? 'r' : '-'));
	ft_putchar((c = st_mode & S_IWUSR ? 'w' : '-'));
	ft_putchar((c = st_mode & S_IXUSR ? 'x' : '-'));
	ft_putchar((c = st_mode & S_IRGRP ? 'r' : '-'));
	ft_putchar((c = st_mode & S_IWGRP ? 'w' : '-'));
	ft_putchar((c = st_mode & S_IXGRP ? 'x' : '-'));
	ft_putchar((c = st_mode & S_IROTH ? 'r' : '-'));
	ft_putchar((c = st_mode & S_IWOTH ? 'w' : '-'));
	ft_putchar((c = st_mode & S_IXOTH ? 'x' : '-'));
}

void	get_info(char *file_name)
{
	struct stat		buff;

	stat(file_name, &buff);
	get_file_type(buff.st_mode);
	get_permission(buff.st_mode);
	ft_putchar(' ');
	ft_putendl(ft_ls_path_to_file(file_name), 0);
}

void	ft_l(char *path_name, t_flags flags)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_data			*head;
	t_data			*node;

	head = NULL;
	if (!(dirp = opendir(path_name)))
		return ;
	while ((dp = readdir(dirp)) != NULL)
	{
		if (*(dp->d_name) == '.')
			if (flags.bits.a == 0)
				continue ;
		node = new_node(dp);
		push_back(&head, node);
	}
	node = head;
	while (node != NULL)
	{
		get_info(ft_str_path(path_name, node->name));
		node = node->next;
	}
	ft_free_list(head);
}

void	ft_l_flag(char **av, int i, int flag, t_flags flags)
{
	if (flag == 0)
	{
		ft_l(".", flags);
		return ;
	}
	while (av[i])
	{
		if (flag > 1)
			ft_putendl(av[i], 1);
		ft_l(av[i], flags);
		if (flag - i >= 0)
			ft_putchar('\n');
		i++;
	}
}
