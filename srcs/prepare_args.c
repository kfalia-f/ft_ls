/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:10:17 by koparker          #+#    #+#             */
/*   Updated: 2019/04/16 15:22:35 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void    ft_nonexistent_argv_error(char *name)
{
	ft_putstr("ft_ls: ");
	ft_putstr(name);
	ft_putstr(": ");
	ft_putstr(strerror(errno));
	ft_putchar('\n');
}

t_data	*ft_convert_args(char **av)
{
	DIR		*dirp;
	t_data	*head;
	size_t	i;

	i = 0;
	head = NULL;
	while (av[i])
	{	
		if ((dirp = opendir(av[i])) == NULL)
		{
			if (errno != 20)
				ft_nonexistent_argv_error(av[i]);
			else
				push_back(&head, new_file(av[i]));
		}
		else
			push_back(&head, new_file(av[i]));
		i++;
	}
	return (head);
}
