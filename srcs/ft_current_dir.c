/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_current_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:52:55 by koparker          #+#    #+#             */
/*   Updated: 2019/04/11 18:01:38 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_data	*ft_current_dir(char *s)
{
	DIR		*dirp;
	t_data	*head;

	head = NULL;
	dirp = opendir(s);
	head = ft_readdir(dirp);
	closedir(dirp);
	return (head);
}

void	ft_set_mtime(t_data	**head)
{
	t_data		*tmp;
	struct stat	buff;

	tmp = *head;
	while (tmp)
	{
		stat(tmp->name, &buff);
		tmp->time = buff.st_mtime;
		tmp = tmp->next;
	}
}

void	ft_process_current_dir(char *s, t_flags fl)
{
	t_data	*head;

	head = ft_current_dir(s);
	if (fl.bits.a == 0 && fl.bits.f == 0)
		ft_skip_starting_dots(&head);
	ft_balanser_sort(&head, fl);
	if (fl.bits.one == 0)
		ft_print(head);
	else
		ft_print_simple(&head);
	ft_free_list(head);
}
