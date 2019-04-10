/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:24:27 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/10 19:51:20 by kfalia-f         ###   ########.fr       */
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

char	*ft_date(char *date)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_memalloc(13);
	while (date[i])
	{
		if (i < 4)
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
	st->date = ft_date(ctime(&buff.st_mtime));
}

static int		ft_max_llen(t_lflag *st, int flag)
{
	t_lflag	*tmp;
	int		sz_len;
	int		sz_max;
	int		ln_len;
	int		ln_max;

	tmp = st;
	sz_max = 0;
	ln_max = 0;
	while (tmp)
	{
		sz_len = ft_strlen(ft_itoa(tmp->file_size));
		ln_len = ft_strlen(ft_itoa(tmp->links));
		if (sz_max < sz_len)
			sz_max = sz_len;
		if (ln_max < ln_len)
			ln_max = ln_len;
		tmp = tmp->next;
	}
	if (flag == 1)
		return (ln_max);
	return (sz_max);
}

void	ft_output_info(t_lflag *st)
{
	t_lflag	*tmp;
	int		max_ln;
	int		max_sz;

	tmp = st;
	max_ln = ft_max_llen(tmp, 1);
	max_sz = ft_max_llen(tmp, 2);
	while (tmp)
	{
		ft_putstr(tmp->permissions);
		ft_output_spaces(' ', 2 + max_ln - ft_strlen(ft_itoa(tmp->links)));
		ft_putnbr(tmp->links);
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->owner);
		ft_output_spaces(' ', 2);
		ft_putstr(tmp->group);
		ft_output_spaces(' ', 2 + max_sz - ft_strlen(ft_itoa(tmp->file_size)));
		ft_putnbr(tmp->file_size);
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->date);
		ft_output_spaces(' ', 1);
		ft_putstr(tmp->file_name);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void	ft_l(char *path_name, t_flags flags)
{
	DIR				*dirp;
	struct stat		buff;
	struct dirent	*dp;
	t_lflag			*lhead;
	t_lflag			*lnode;

	lhead = NULL;
	if (!(dirp = opendir(path_name)))
		return ;
	while ((dp = readdir(dirp)) != NULL)
	{
		if (*(dp->d_name) == '.')
			if (flags.bits.a == 0)
				continue ;
		lnode = new_l_node(dp);
		l_push_back(&lhead, lnode);
	}
	lnode = lhead;
	while (lnode != NULL)
	{
		get_info(ft_str_path(path_name, lnode->file_name), lnode);
		lnode = lnode->next;
	}
	stat(path_name, &buff);
	printf ("total %lld\n", buff.st_blocks);
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
