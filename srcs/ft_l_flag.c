/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:24:27 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/10 17:07:49 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	ft_print_spaces(int n)
{
	while (n-- > 0)
		ft_putchar(' ');
}

char	get_file_type(mode_t st_mode)
{
	if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISREG(st_mode))
		return ('-');
	return ('d');
}

char	*get_permission(mode_t st_mode)
{
	char	*str;
	int		i;

	str = ft_memalloc(11);
	i = 0;
	str[i++] = get_file_type(st_mode);
	str[i++] = st_mode & S_IRUSR ? 'r' : '-';
	str[i++] = st_mode & S_IWUSR ? 'w' : '-';
	str[i++] = st_mode & S_IXUSR ? 'x' : '-';
	str[i++] = st_mode & S_IRGRP ? 'r' : '-';
	str[i++] = st_mode & S_IWGRP ? 'w' : '-';
	str[i++] = st_mode & S_IXGRP ? 'x' : '-';
	str[i++] = st_mode & S_IROTH ? 'r' : '-';
	str[i++] = st_mode & S_IWOTH ? 'w' : '-';
	str[i++] = st_mode & S_IXOTH ? 'x' : '-';
	str[i] = '\0';
	return (str);
}

void	get_info(char *file_name, t_lflag *st)
{
	struct stat		buff;
	struct passwd	*pwd;
	struct group	*gr;

	stat(file_name, &buff);
	pwd = getpwuid(buff.st_uid);  
	st->permissions = get_permission(buff.st_mode); //permissions (r/w/x)
	ft_putstr("FLAG");
	printf("%s", st->permissions);
	ft_print_spaces(2);
	ft_putnbr(buff.st_nlink);     //num of links for file
	ft_putchar('\t');
	ft_putstr(pwd->pw_name);      //owner name
	ft_print_spaces(1);
	gr = getgrgid(buff.st_gid);   //group name
	ft_putstr(gr->gr_name);
	gr = getgrgid(buff.st_gid);
	ft_print_spaces(1);
	ft_putendl(ft_ls_path_to_file(file_name), 0); //filename
}

void	ft_l(char *path_name, t_flags flags)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_data			*head;
	t_data			*node;
	t_lflag			*st;

	head = NULL;
	st = NULL;
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
		get_info(ft_str_path(path_name, node->name), st);
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
