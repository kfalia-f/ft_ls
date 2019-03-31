/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recurcion_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 20:04:59 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/03/31 20:35:51 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		ft_files();



void	ft_recurcion_flag(char **av, int i, int flag)
{
	*DIR			*dirp;
	struct dirent	*dp;

	if (flag == 0)
	{
		printf("FLAG");
	}
	while (av[i])
	{
		ft_recurs(
	}
}
