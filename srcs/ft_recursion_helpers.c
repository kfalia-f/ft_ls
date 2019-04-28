/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursion_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <kfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:50:42 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/28 16:16:46 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

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
		stat(tmp->name, &buff);
		if (S_ISREG(buff.st_mode))
			push_back(&new, new_file(tmp->name));
		tmp = tmp->next;
	}
	if (new)
		i = ft_rfile_out(new, fl);
	return (i);
}
