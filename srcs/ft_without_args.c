/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_without_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 20:01:59 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/03/23 20:38:33 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
**Need to rework
*/

void	ft_without_args(char *str)
{
	DIR				*dirp;
	struct dirent	*dp;

	dirp = opendir(str);
	while ((dp = readdir(dirp)) != NULL)
		ft_putendl(dp->d_name, 0);
}
