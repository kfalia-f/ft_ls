/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_current_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:52:55 by koparker          #+#    #+#             */
/*   Updated: 2019/04/24 16:55:05 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_data	*ft_current_dir(char *s, t_flags fl)
{
	DIR		*dirp;
	t_data	*head;

	head = NULL;
	dirp = opendir(s);
	head = ft_readdir(dirp, fl);
	closedir(dirp);
	return (head);
}

void	ft_set_time(t_data **head, t_flags fl, char *path)
{
	t_data		*tmp;
	struct stat	buff;

	tmp = *head;
	while (tmp)
	{
		if (path == NULL)
			stat(tmp->name, &buff);
		else
			lstat(ft_str_path(path, tmp->name), &buff);
		if (fl.bits.upper_u == 1)
			tmp->time = buff.st_birthtime;
		else if (fl.bits.u == 1)
			tmp->time = buff.st_atime;
		else
			tmp->time = buff.st_mtime;
		tmp = tmp->next;
	}
}

/*void	ft_output_upper_g_one(char *s)
{
	t_data	*node;
	t_data	*tmp;

	node = new_file(s);
	ft_set_permissions(&node, NULL);
	tmp = node;
	while (tmp)
	{
		ft_colorized_output(tmp->perm, tmp->name);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	ft_free_list(node);
}*/

void	ft_process_current_dir(char *s, t_flags fl)
{
	t_data	*head;

	if (fl.bits.d)
	{
		if (fl.bits.l && !fl.bits.one)
			ft_simple_l(new_file("."), fl);
		else
		{
			if (!fl.bits.upper_g)
				ft_putendl(s, 0);
			else
			{
			//	ft_output_upper_g_one(s);
				ft_putendl(ft_strjoin(DIR_COLOR, s), 0);
			}
		}
		return ;
	}
	if (fl.bits.l && !fl.bits.one)
	{
		ft_l(".", fl);
		return ;
	}
	head = ft_current_dir(s, fl);
	ft_output(head, fl, 1, NULL);
}
