/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:24:27 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/18 17:39:44 by koparker         ###   ########.fr       */
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

void	get_info(char *path, t_data *st, t_flags fl)
{
	struct stat		buff;
	struct passwd	*pwd;
	struct group	*gr;

	if ((lstat(path, &buff)) != 0)
		ft_putstr("ERROR_STAT");
	pwd = getpwuid(buff.st_uid);   //owner name 
	gr = getgrgid(buff.st_gid);   //group name

	st->l_info->owner = ft_strcpy(ft_memalloc(ft_strlen(pwd->pw_name)), pwd->pw_name); //owner
	st->l_info->group = ft_strcpy(ft_memalloc(ft_strlen(gr->gr_name)), gr->gr_name);  //group
	st->l_info->date = ft_date(ctime(&buff.st_mtime), buff.st_mtime);
	st->l_info->links = buff.st_nlink;  //num of links
	st->l_info->permissions = get_permission(buff.st_mode, path); //permissions (r/w/x) + file type
	if (*(st->l_info->permissions) != 'c' && *(st->l_info->permissions) != 'b')
		st->l_info->file_size = buff.st_size; //file_size
	else
	{
		st->l_info->maj = major(buff.st_rdev);
		st->l_info->min = minor(buff.st_rdev);
	}
	if (S_ISLNK(buff.st_mode))
		ft_link(st, path, 0, fl);
}

static int		ft_max_llen(t_data *st, int flag)  //1 = link; 2 = size; 3 = owner; 4 = group 5 = maj 6 = min
{
	t_data	*tmp;
	int		len;
	int		max;

	tmp = st;
	max = 0;
	while (tmp)
	{
		if (flag == 1)
			len = ft_strlen(ft_itoa(tmp->l_info->links));
		else if (flag == 2)
			len = ft_strlen(ft_itoa(tmp->l_info->file_size));
		else if (flag == 3)
			len = ft_strlen(tmp->l_info->owner);
		else if (flag == 4)
			len = ft_strlen(tmp->l_info->group);
		else if (flag == 5)
			len = ft_strlen(ft_itoa(tmp->l_info->maj));
		else if (flag == 6)
			len = ft_strlen(ft_itoa(tmp->l_info->min));
		if (max < len)
			max = len;
		tmp = tmp->next;
	}
	return (max);
}

void	ft_output_info(t_data *st, t_flags fl)
{
	t_data	*tmp;
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
		ft_putstr(tmp->l_info->permissions);
		ft_output_spaces(' ', 1 + arr[0] - ft_strlen(ft_itoa(tmp->l_info->links)));
		ft_putnbr(tmp->l_info->links);
		ft_output_spaces(' ', 1);
		if (!fl.bits.g)
		{
			ft_putstr(tmp->l_info->owner);
			ft_output_spaces(' ', 2 + arr[2] - ft_strlen(tmp->l_info->owner));
		}
		ft_putstr(tmp->l_info->group);
		ft_output_spaces(' ', 2 + arr[3] - ft_strlen(tmp->l_info->group) + arr[1] - ft_strlen(ft_itoa(tmp->l_info->file_size)));
		if (*(tmp->l_info->permissions) != 'c' && *(tmp->l_info->permissions) != 'b')
			ft_putnbr(tmp->l_info->file_size);
		else
		{
			ft_output_spaces(' ', 1 + arr[4] - ft_strlen(ft_itoa(tmp->l_info->maj)));
			ft_putnbr(tmp->l_info->maj);
			ft_putchar(',');
			ft_output_spaces(' ', 1 + arr[5] - ft_strlen(ft_itoa(tmp->l_info->min)));
			ft_putnbr(tmp->l_info->min);
		}
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->l_info->date);
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->l_info->file_name);
		if (tmp->l_info->link)
			ft_putstr(tmp->l_info->link);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

int		ft_total(char *path_name, t_data *st)
{
	struct stat	buff;
	t_data		*tmp;
	int			total;

	tmp = st;
	total = 0;
	while (tmp)
	{
		stat(ft_str_path(path_name, tmp->name), &buff);
		total += buff.st_blocks;
		tmp = tmp->next;
	}
	return (total);
}

void	ft_l(char *path_name, t_flags flags)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_data			*lhead;
	t_data			*lnode;

	lhead = NULL;
	if (!(dirp = opendir(path_name)))
		return ;
	while ((dp = readdir(dirp)) != NULL)
	{
		if (*(dp->d_name) == '.')
			if (flags.bits.a == 0 && flags.bits.f == 0)
				continue ;
		lnode = new_node(dp);
		push_back(&lhead, lnode);
	}
	if (lhead)
		ft_balanser_sort(&lhead, flags, path_name);
	lnode = lhead;
	while (lnode)
	{
		new_l_node(&lnode, lnode->name);
		get_info(ft_str_path(path_name, lnode->name), lnode, flags);
		lnode = lnode->next;
	}
	if (lhead)
	{
		ft_putstr("total ");
		ft_putnbr(ft_total(path_name, lhead));
		ft_putchar('\n');
	}
	ft_output_info(lhead, flags);
	//ft_free_list(lhead);
}

void	ft_file(t_data *av, t_flags fl)
{
	new_l_node(&av, av->name);
	get_info(av->name, av, fl);
	ft_output_info(av, fl);
}

void	ft_l_flag(t_data *av, int flag, t_flags flags)
{
	struct stat	buff;
	t_data		*head;

	if (flag > 1)
		ft_balanser_sort(&av, flags, NULL);
	head = av;
	if (flag == 0)
	{
		ft_l(".", flags);
		return ;
	}
	while (av)
	{
		lstat(av->name, &buff);
		if (S_ISLNK(buff.st_mode))
			ft_link(av, av->name, 1, flags);
		if (S_ISREG(buff.st_mode))
			ft_file(av, flags);
		av = av->next;
	}
	av = head;
	while (av)
	{
		lstat(av->name, &buff);
		if (S_ISLNK(buff.st_mode) || S_ISREG(buff.st_mode))
		{
			av = av->next;
			continue ;
		}
		if (flag > 1)
			ft_putendl(av->name, 1);
		ft_l(av->name, flags);
		if (av->next)
			ft_putchar('\n');
		av = av->next;
	}
}
