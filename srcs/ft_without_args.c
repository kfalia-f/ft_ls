/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_without_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 20:01:59 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/04 15:43:50 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_without_args(char *str)
{
	DIR				*dirp;
	t_data			*head;

	head = NULL;
	dirp = opendir(str);
	head = ft_readdir(dirp);
	closedir(dirp);
	ft_print_without_args(ft_ascii_sort(&head));
}
