/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_current_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:52:55 by koparker          #+#    #+#             */
/*   Updated: 2019/04/18 15:36:09 by koparker         ###   ########.fr       */
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

void	ft_process_current_l(t_data **head)
{
	t_data	*tmp;

	tmp = *head;

}

void	ft_process_current_dir(char *s, t_flags fl)
{
	t_data	*head;

	head = ft_current_dir(s, fl);
	if (fl.bits.d == 1)
	{
		if (fl.bits.l == 1)
			ft_process_current_l(&head);
		else
			ft_putendl(s, 0);
		return ;
	}
	ft_output(head, fl, 1, NULL);
}
