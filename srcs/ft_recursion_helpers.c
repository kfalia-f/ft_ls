/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursion_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:50:42 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/05/13 15:11:43 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_error(char *path, char *file)
{
	ft_putchar_base('\n', 1);
	ft_putstr_base(path, 1);
	ft_putstr_base(":\n", 1);
	ft_putstr_base("ft_ls: ", 2);
	ft_putstr_base(file, 2);
	ft_putstr_base(": ", 2);
	ft_putstr_base(strerror(errno), 2);
	ft_putchar_base('\n', 2);
}

int		ft_rfile_out(t_data *new, t_flags fl)
{
	int i;

	i = ft_list_size(new);
	if (fl.bits.l)
		ft_simple_l(new, fl);
	else
	{
		ft_print(new, fl, new->name);
		ft_free_list(&new, 0);
	}
	return (i);
}

int		ft_dot(t_data *head, t_flags fl, int i, int flag)
{
	DIR			*dirp;
	struct stat	buff;
	t_data		*tmp;
	t_data		*new;

	tmp = head;
	if (tmp == NULL && flag == 0)
	{
		dirp = opendir(".");
		ft_recurs(".", dirp, fl);
		closedir(dirp);
		return (-1);
	}
	new = NULL;
	while (tmp)
	{
		lstat(tmp->name, &buff);
		if (S_ISREG(buff.st_mode) || S_ISLNK(buff.st_mode))
			push_back(&new, new_file(tmp->name));
		tmp = tmp->next;
	}
	if (new)
		i = ft_rfile_out(new, fl);
	return (i);
}
