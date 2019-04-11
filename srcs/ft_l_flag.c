/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:24:27 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/11 17:26:16 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_print_spaces(int n)
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

char	*ft_date(char *date, size_t tm)
{
	char	*str;
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	if (time(NULL) - tm > 15552000)
		flag = 1;
	str = ft_memalloc(13);
	while (date[i] != '\n')
	{
		if (i < 4)
		{
			i++;
			continue ;
		}
		if (flag == 1 && i >= 11 && i <	19)
		{
			i++;
			continue ;
		}
		if (i == 16)
			break ;
		str[j] = date[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

void	get_info(char *file_name, t_lflag *st)
{
	struct stat		buff;
	struct passwd	*pwd;
	struct group	*gr;

	stat(file_name, &buff);
	pwd = getpwuid(buff.st_uid);   //owner name 
	gr = getgrgid(buff.st_gid);   //group name

	st->links = buff.st_nlink;  //num of links
	st->file_size = buff.st_size; //file_size
	st->permissions = get_permission(buff.st_mode); //permissions (r/w/x) + file type
	st->owner = ft_strcpy(ft_memalloc(ft_strlen(pwd->pw_name)), pwd->pw_name); //owner
	st->group = ft_strcpy(ft_memalloc(ft_strlen(gr->gr_name)), gr->gr_name);  //group
	st->date = ft_date(ctime(&buff.st_mtime), buff.st_mtime);
}

static int		ft_max_llen(t_lflag *st, int flag)  //1 = link; 2 = size; 3 = owner; 4 = group
{
	t_lflag	*tmp;
	int		len;
	int		max;

	tmp = st;
	max = 0;
	while (tmp)
	{
		if (flag == 1)
			len = ft_strlen(ft_itoa(tmp->links));
		else if (flag == 2)
			len = ft_strlen(ft_itoa(tmp->file_size));
		else if (flag == 3)
			len = ft_strlen(tmp->owner);
		else if (flag == 4)
			len = ft_strlen(tmp->group);
		if (max < len)
			max = len;
		tmp = tmp->next;
	}
	return (max);
}

void	ft_output_info(t_lflag *st)
{
	t_lflag	*tmp;
	int		arr[4];

	tmp = st;
	arr[0] = ft_max_llen(st, 1);
	arr[1] = ft_max_llen(st, 2);
	arr[2] = ft_max_llen(st, 3);
	arr[3] = ft_max_llen(st, 4);
	while (tmp)
	{
		ft_putstr(tmp->permissions);
		ft_output_spaces(' ', 2 + arr[0] - ft_strlen(ft_itoa(tmp->links)));
		ft_putnbr(tmp->links);
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->owner);
		ft_output_spaces(' ', 2 + arr[2] - ft_strlen(tmp->owner));
		ft_putstr(tmp->group);
		ft_output_spaces(' ', 2 + arr[3] - ft_strlen(tmp->group) + arr[1] - ft_strlen(ft_itoa(tmp->file_size)));
		ft_putnbr(tmp->file_size);
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->date);
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->file_name);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

int		ft_total(char *path_name, t_lflag *st)
{
	struct stat	buff;
	t_lflag 	*tmp;
	int			total;

	tmp = st;
	total = 0;
	while (tmp)
	{
		stat(ft_str_path(path_name, tmp->file_name), &buff);
		total += buff.st_blocks;
		tmp = tmp->next;
	}
	return (total);
}

void	ft_l(char *path_name, t_flags flags)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_lflag			*lhead;
	t_lflag			*lnode;

	lhead = NULL;
	if (!(dirp = opendir(path_name)))
		return ;
	while ((dp = readdir(dirp)) != NULL)
	{
		if (*(dp->d_name) == '.')
			if (flags.bits.a == 0 && flags.bits.f == 0)
				continue ;
		lnode = new_l_node(dp);
		l_push_back(&lhead, lnode);
	}
	lnode = ft_l_ascii_sort(&lhead);
	while (lnode != NULL)
	{
		get_info(ft_str_path(path_name, lnode->file_name), lnode);
		lnode = lnode->next;
	}
	ft_putstr("total ");
	ft_putnbr(ft_total(path_name, lhead));
	ft_putchar('\n');
	ft_output_info(lhead);
	//ft_free_list(lhead);
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
