/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:26:06 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/21 17:43:13 by kfalia-f         ###   ########.fr       */
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
