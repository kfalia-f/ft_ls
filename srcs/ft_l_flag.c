/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <kfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:24:27 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/28 17:23:03 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_link(t_data *av, char *path)
{
	char	link[4096];

	ft_bzero(link, 4096);
	readlink(path, link, 4096);
	free(av->l_info->file_name);
	av->l_info->file_name = ft_strjoin(av->name, " ");
	av->l_info->link = ft_strjoin("-> ", link);
}

t_data	*ft_new(t_data *av)
{
	struct stat	buff;
	t_data		*new;

	new = NULL;
	while (av)
	{
		lstat(av->name, &buff);
		if (S_ISLNK(buff.st_mode) || S_ISREG(buff.st_mode))
			push_back(&new, new_file(av->name));
		av = av->next;
	}
	return (new);
}

int		ft_forl(t_data *head, t_flags fl)
{
	t_data		*av;
	t_data		*new;
	int			i;

	av = head;
	new = ft_new(av);
	i = ft_list_size(new);
	av = new;
	while (new)
	{
		new_l_node(&new, new->name, fl);
		get_info(new->name, new, fl);
		new = new->next;
	}
	ft_output_info(av, fl);
	if (i > 0)
		ft_free_list(&av, 1);
	return (i);
}

void	ft_l_flag(t_data *av, int flag, t_flags flags)
{
	struct stat	buff;
	int			i;
	t_data		*head;

	ft_balanser_sort(&av, flags, NULL);
	i = ft_forl(av, flags);
	head = av;
	while (av)
	{
		lstat(av->name, &buff);
		if (S_ISLNK(buff.st_mode) || S_ISREG(buff.st_mode))
		{
			av = av->next;
			continue ;
		}
		if (i > 0)
			ft_putendl(av->name, 2);
		else if (flag > 1)
			ft_putendl(av->name, 1);
		ft_l(av->name, flags);
		if (!i && av->next)
			ft_putchar('\n');
		av = av->next;
	}
	ft_free_list(&head, 0);
}
