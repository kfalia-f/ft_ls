/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:28:59 by koparker          #+#    #+#             */
/*   Updated: 2019/03/29 18:58:37 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

// read argv
t_data	*ft_read_data(char *str)
{
	// opendir, read data, closedir. Output error OR Store errors
	DIR				*dirp;
	struct dirent	*dp;
	t_data			*head;
	t_data			*node;

	head = NULL;
	if (!(dirp = opendir(str)))
	{
		// use 'stat' to obtain info dir OR file (not errno code)
		if (errno != 20)
		{
			ft_putstr("ft_ls: ");
			ft_putstr(str);
			ft_putstr(": ");
			ft_putstr(strerror(errno));
			ft_putchar('\n');
		}
		else
		{
			node = new_file(str);
			push_back(&head, node);
			return (head);
			// node who accepts char *, but doesn't need dp
		}
		return (NULL);
	}
	while ((dp = readdir(dirp)) != NULL)
	{
		node = new_node(dp);
		push_back(&head, node);
	}
	closedir(dirp);
	return (head);
}

// fill external list
t_argv	*ft_argv(char **av)
{
	t_argv	*head;
	t_argv	*node;
	int		i;

	i = 0;
	head = NULL;
	while (av[i] != NULL)
	{
		node = new_argv(av[i]);
		if ((node->data = ft_read_data(av[i])) == NULL)
		{
			i++;
			continue ;
		}
		push_back_argv(&head, node);
		i++;
	}
	return (head);
}
