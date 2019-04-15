/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_current_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:52:55 by koparker          #+#    #+#             */
/*   Updated: 2019/04/15 16:17:15 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_data	*ft_current_dir(char *s)
{
	DIR		*dirp;
	t_data	*head;
	t_flags fl;

	head = NULL;
	fl.value = 0;
	dirp = opendir(s);
	head = ft_readdir(dirp, fl);
	closedir(dirp);
	return (head);
}

void	ft_set_time(t_data **head, t_flags fl)
{
	t_data		*tmp;
	struct stat	buff;

	tmp = *head;
	while (tmp)
	{
		stat(tmp->name, &buff);
		if (fl.bits.upper_u == 1)
			tmp->time = buff.st_birthtime;
		else if (fl.bits.u == 1)
			tmp->time = buff.st_atime;
		else
			tmp->time = buff.st_mtime;
		tmp = tmp->next;
	}
}

void	ft_process_current_dir(char *s, t_flags fl)
{
	t_data	*head;

	head = ft_current_dir(s);
	ft_output(head, fl, 1, NULL);
}
