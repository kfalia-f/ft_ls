/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursion_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <kfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:32:11 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/28 15:06:02 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		ft_only_files(t_data *head, char *path_name)
{
	struct stat		buff;
	t_data			*tmp;
	char			*path;

	tmp = head;
	while (tmp)
	{
		if (*(tmp->name) == '.')
		{
			tmp = tmp->next;
			continue ;
		}
		path = ft_str_path(path_name, tmp->name);
		stat(path, &buff);
		free(path);
		if (S_ISDIR(buff.st_mode))
			return (0);
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}

void	ft_rec(t_data *tmp, char *pt, t_flags fl)
{
	DIR				*dirp2;
	char			*path;

	while (tmp)
	{
		if (!ft_strcmp(tmp->name, ".") || !ft_strcmp(tmp->name, ".."))
		{
			tmp = tmp->next;
			continue ;
		}
		path = ft_str_path(pt, tmp->name);
		if ((dirp2 = opendir(path)))
		{
			ft_putendl(path, 2);
			ft_recurs(path, dirp2, fl);
			closedir(dirp2);
		}
		tmp = tmp->next;
		free(path);
	}
}

void	ft_recurs(char *path_name, DIR *dirp, t_flags fl)
{
	t_data			*head;
	t_data			*tmp;
	char			*pt;

	head = ft_readdir(dirp, fl);
	ft_balanser_sort(&head, fl, path_name);
	tmp = head;
	pt = ft_strjoin(path_name, "/");
	if (ft_only_files(head, pt))
	{
		ft_output(head, fl, 1, pt);
		free(pt);
		return ;
	}
	head = tmp;
	if (tmp)
		ft_output(tmp, fl, 0, pt);
	if (!fl.bits.a && !fl.bits.f)
		ft_remove_dots(&tmp);
	ft_rec(tmp, pt, fl);
	ft_free_list(&head, 0);
	free(pt);
}

int		ft_dot(t_data *head, t_flags fl)
{
	DIR			*dirp;
	struct stat	buff;
	t_data		*tmp;
	t_data		*new;
	int			i;

	tmp = head;
	if (tmp == NULL)
	{
		dirp = opendir(".");
		ft_recurs(".", dirp, fl);
		closedir(dirp);
		return (-1);
	}
	new = NULL;
	while (tmp)
	{
		stat(tmp->name, &buff);
		if (S_ISREG(buff.st_mode))
			push_back(&new, new_file(tmp->name));
		tmp = tmp->next;
	}
	i = ft_list_size(new);
	if (new)
	{
		if (fl.bits.l)
			ft_simple_l(new, fl);
		else
			ft_print(new, fl);
	}
	return (i);
}

void	ft_recursion_flag(t_data *av, int flag, t_flags fl)
{
	DIR			*dirp;
	t_data		*head;
	int			i;

	if (fl.bits.d)
		return ;
	head = av;
	if (head)
		ft_balanser_sort(&head, fl, head->name);
	i = ft_dot(head, fl);
	if (i == -1)
		return ;
	while (head)
	{
		if ((dirp = opendir(head->name)))
		{
			if (i == 0 && flag > 1 && (i += 1))
				ft_putendl(head->name, 1);
			else if (flag > 1)
				ft_putendl(head->name, 2);
			ft_recurs(head->name, dirp, fl);
			closedir(dirp);
		}
		head = head->next;
	}
}
