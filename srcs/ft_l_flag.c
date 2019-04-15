/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:24:27 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/15 21:05:36 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char	get_file_type(mode_t st_mode)
{
	if (S_ISREG(st_mode))
		return ('-');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISFIFO(st_mode))
		return ('p');
	return ('s');
}

char	get_acl(char *path)
{
	acl_t		acl;
	acl_entry_t	dummy;
	int			xattr;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (xattr > 0)
		return ('@');
	else if (acl != NULL)
		return ('+');
	return (' ');
}

char	*get_permission(mode_t st_mode, char *path)
{
	char	*str;

	str = ft_memalloc(12);
	str[0] = get_file_type(st_mode);
	str[1] = st_mode & S_IRUSR ? 'r' : '-';
	str[2] = st_mode & S_IWUSR ? 'w' : '-';
	str[3] = st_mode & S_IXUSR ? 'x' : '-';
	str[4] = st_mode & S_IRGRP ? 'r' : '-';
	str[5] = st_mode & S_IWGRP ? 'w' : '-';
	str[6] = st_mode & S_IXGRP ? 'x' : '-';
	str[7] = st_mode & S_IROTH ? 'r' : '-';
	str[8] = st_mode & S_IWOTH ? 'w' : '-';
	str[9] = st_mode & S_IXOTH ? 'x' : '-';
	str[10] = get_acl(path);
	if (st_mode & 2048)
		str[3] = str[3] == 'x' ? 's' : 'S';
	if (st_mode & 1024)
		str[6] = str[6] == 'x' ? 's' : 'S';
	if (st_mode & 512)
		str[9] = str[9] == 'x' ? 't' : 'T';
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

	if ((lstat(file_name, &buff)) != 0)
		ft_putstr("ERROR_STAT");
	pwd = getpwuid(buff.st_uid);   //owner name 
	gr = getgrgid(buff.st_gid);   //group name

	st->owner = ft_strcpy(ft_memalloc(ft_strlen(pwd->pw_name)), pwd->pw_name); //owner
	st->group = ft_strcpy(ft_memalloc(ft_strlen(gr->gr_name)), gr->gr_name);  //group
	st->date = ft_date(ctime(&buff.st_mtime), buff.st_mtime);
	st->links = buff.st_nlink;  //num of links
	st->permissions = get_permission(buff.st_mode, file_name); //permissions (r/w/x) + file type
	if (*(st->permissions) != 'c' && *(st->permissions) != 'b')
		st->file_size = buff.st_size; //file_size
	else
	{
		st->maj = major(buff.st_rdev);
		st->min = minor(buff.st_rdev);
	}
}

static int		ft_max_llen(t_lflag *st, int flag)  //1 = link; 2 = size; 3 = owner; 4 = group 5 = maj 6 = min
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
		else if (flag == 5)
			len = ft_strlen(ft_itoa(tmp->maj));
		else if (flag == 6)
			len = ft_strlen(ft_itoa(tmp->min));
		if (max < len)
			max = len;
		tmp = tmp->next;
	}
	return (max);
}

void	ft_output_info(t_lflag *st)
{
	t_lflag	*tmp;
	int		arr[6];

	tmp = st;
	arr[0] = ft_max_llen(st, 1);
	arr[1] = ft_max_llen(st, 2);
	arr[2] = ft_max_llen(st, 3);
	arr[3] = ft_max_llen(st, 4);
	arr[4] = ft_max_llen(st, 5);
	arr[5] = ft_max_llen(st, 6);
	while (tmp)
	{
		ft_putstr(tmp->permissions);
		ft_output_spaces(' ', 1 + arr[0] - ft_strlen(ft_itoa(tmp->links)));
		ft_putnbr(tmp->links);
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->owner);
		ft_output_spaces(' ', 2 + arr[2] - ft_strlen(tmp->owner));
		ft_putstr(tmp->group);
		ft_output_spaces(' ', 2 + arr[3] - ft_strlen(tmp->group) + arr[1] - ft_strlen(ft_itoa(tmp->file_size)));
		if (*(tmp->permissions) != 'c' && *(tmp->permissions) != 'b')
			ft_putnbr(tmp->file_size);
		else
		{
			ft_output_spaces(' ', 1 + arr[4] - ft_strlen(ft_itoa(tmp->maj)));
			ft_putnbr(tmp->maj);
			ft_putchar(',');
			ft_output_spaces(' ', 1 + arr[5] - ft_strlen(ft_itoa(tmp->min)));
			ft_putnbr(tmp->min);
		}
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->date);
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->file_name);
		if (tmp->link)
			ft_putstr(tmp->link);
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
	if (lhead->next != NULL)
		lnode = ft_l_ascii_sort(&lhead);
	while (lnode)
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

void	ft_arg_link(char *path_name)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_lflag			*st;
	char			link[4096];

	st = NULL;
	if (!(dirp = opendir(ft_ls_path_to_file(path_name, 0))))
		return ;
	while ((dp = readdir(dirp)))
	{
		if (ft_strcmp(dp->d_name, ft_ls_path_to_file(path_name, 1)) == 0)
			break ;
		//else
		//	ft_putendl("Wrong path", 0);
	}
	st = new_l_node(dp);
	get_info(path_name, st);
	readlink(path_name, link, 4096);
	st->link = (char *)malloc(sizeof(char) * (ft_strlen(link + 5)));
	st->file_name = ft_strjoin(path_name, " ");              //mb leak
	st->link = ft_strjoin("-> ", link);
	ft_output_info(st);
	//free
}

void	ft_file(char *file_name)
{
	DIR 			*dirp;
	struct dirent	*dp;
	t_lflag			*lhead;

	dirp = opendir(ft_ls_path_to_file(file_name, 0));
	while ((dp = readdir(dirp)))
		if (ft_strcmp(dp->d_name, ft_ls_path_to_file(file_name, 1)) == 0)
			break ;
	lhead = new_l_node(dp);
	closedir(dirp);
	get_info(file_name, lhead);
	ft_output_info(lhead);
}

void	ft_l_flag(char **av, int i, int flag, t_flags flags)
{
	struct stat	buff;
	int 			k;

	k = i;
	if (flag == 0)
	{
		ft_l(".", flags);
		return ;
	}
	while (av[k])
	{
		lstat(av[k], &buff);
		if (S_ISLNK(buff.st_mode))
			ft_arg_link(av[k]);
		if (S_ISREG(buff.st_mode))
			ft_file(av[k]);
		k++;
	}
	ft_putchar('\n');
	while (av[i])
	{
		lstat(av[i], &buff);
		if (S_ISLNK(buff.st_mode))
		{
			i++;
			continue ;
		}
		else if (S_ISREG(buff.st_mode))
		{
			i++;
			continue ;
		}
		if (flag > 1)
			ft_putendl(av[i], 1);
		ft_l(av[i], flags);
		if (i < k)
			ft_putchar('\n');
		i++;
	}
}
