/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_get_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:03:22 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/24 19:40:25 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char    get_file_type(mode_t st_mode)
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

char    get_acl(char *path)
{
	acl_t       acl;
	acl_entry_t dummy;
	int         xattr;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (acl != NULL)
	{
		acl_free(acl);
		acl = NULL;
		return ('+');
	}
	else if (xattr > 0)
		return ('@');
	return (' ');
}

char    *get_permission(mode_t st_mode, char *path)
{
	char    *str;

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

char    *ft_date(char *date, size_t tm)
{
	char    *str;
	int     i;
	int     j;
	int     flag;

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
		if (flag == 1 && i >= 11 && i < 19)
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

void    get_info(char *path, t_data *st, t_flags fl)
{
	struct stat     buff;
	struct passwd   *pwd;
	struct group    *gr;

	if ((lstat(path, &buff)) != 0)
		ft_putstr("ERROR_STAT");
	pwd = getpwuid(buff.st_uid);   //owner name
	gr = getgrgid(buff.st_gid);   //group name

	st->l_info->owner = ft_strcpy(ft_memalloc(ft_strlen(pwd->pw_name)), pwd->pw_name); //owner
	st->l_info->group = ft_strcpy(ft_memalloc(ft_strlen(gr->gr_name)), gr->gr_name);  //group
	time_balanser_get_info(st, fl, buff); //date & time
	st->l_info->links = buff.st_nlink;  //num of links
	st->l_info->permissions = get_permission(buff.st_mode, path); //permissions (r/w/x) + file type
	if (*(st->l_info->permissions) != 'c' && *(st->l_info->permissions) != 'b')
	{
		st->l_info->file_size = buff.st_size; //file_size
		st->l_info->maj = 0;
		st->l_info->min = 0;
	}
	else
	{
		st->l_info->maj = major(buff.st_rdev);
		st->l_info->min = minor(buff.st_rdev);
	}
	if (S_ISLNK(buff.st_mode))
		ft_link(st, path, 0, fl);
}
