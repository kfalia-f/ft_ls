/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:24:27 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/21 18:08:51 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void    ft_link(t_data *av, char *path, int flag, t_flags fl)
{
	char            link[4096];

	ft_bzero(link, 4096);
	if (flag)
	{
		new_l_node(&av, av->name, fl);
		get_info(av->name, av, fl);
	}
	else
	{
		readlink(path, link, 4096);
		av->l_info->link = (char *)malloc(sizeof(char) * (ft_strlen(link + 4)));
		av->l_info->file_name = ft_strjoin(av->name, " ");              //mb leak
		av->l_info->link = ft_strjoin("-> ", link);
	}
	if (flag)
		ft_output_info(av, fl, -1);
}

void	ft_file(t_data *av, t_flags fl)
{
	new_l_node(&av, av->name, fl);
	get_info(av->name, av, fl);
	free(av->l_info->file_name);
	av->l_info->file_name = ft_strjoin("", av->name);
	ft_output_info(av, fl, -1);
}

int		ft_forl(t_data *head, t_flags fl)
{
	struct stat	buff;
	t_data		*av;
	int			i;

	i = 0;
	av = head;
	while (av)
	{
		lstat(av->name, &buff);
		if (S_ISLNK(buff.st_mode) && (i += 1))
		{
			ft_link(av, av->name, 1, fl);
			av = av->next;
			continue ;
		}
		if (S_ISREG(buff.st_mode) && (i += 1))
		{
			ft_file(av, fl);
			av = av->next;
			continue ;
		}
		av = av->next;
	}
	return (i);
}

void	ft_l_flag(t_data *av, int flag, t_flags flags)
{
	struct stat	buff;
	int			i;

	if (flag > 1)
		ft_balanser_sort(&av, flags, NULL);
	i = ft_forl(av, flags);
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
}
