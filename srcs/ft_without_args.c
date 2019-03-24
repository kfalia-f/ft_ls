/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_without_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 20:01:59 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/03/24 15:27:45 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
**Need to rework
*/

static void	ft_without_args_true(char *str)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_data			*head;
	t_data			*node;

	head = NULL;
	dirp = opendir(str);
	while ((dp = readdir(dirp)) != NULL)
	{
		node = new_node(dp);
		push_back(&head, node);
	}
	closedir(dirp);
	// ascii sort
	node = ft_ascii_sort(&head);
	// print sorted list
	head = node;
	while (head->next)
	{
		printf("%s\t", head->name);
		head = head->next;
	}
	printf("%s\n", head->name);
	// split to columns
	// print
}

void		ft_without_args(char *str)
{
	DIR				*dirp;
	struct dirent	*dp;

	if (TRUE_LS == 1)
	{
		ft_without_args_true(str);
		return ;
	}	
	dirp = opendir(str);
	while ((dp = readdir(dirp)) != NULL)
		ft_putendl(dp->d_name, 0);
	closedir(dirp);
}
