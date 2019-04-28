/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:37:03 by koparker          #+#    #+#             */
/*   Updated: 2019/04/28 20:18:05 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_argv_error(char *name)
{
	char	*tmp;

	tmp = NULL;
	if (errno == 13)
	{
		ft_putchar('\n');
		ft_putendl(name, 1);
		if ((tmp = ft_strchr(name, '/')) != NULL)
		{
			while (*tmp == '/')
				tmp++;
			name = tmp;
		}
	}
	ft_putstr_base("ft_ls: ", 2);
	ft_putstr_base(name, 2);
	ft_putstr_base(": ", 2);
	ft_putstr_base(strerror(errno), 2);
	ft_putchar_base('\n', 2);
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
			if (errno != 20 && errno != 13)
				ft_argv_error(av[i]);
			else
				push_back(&head, new_file(av[i]));
		}
		else
		{
			push_back(&head, new_file(av[i]));
			closedir(dirp);
		}
		i++;
	}
	return (head);
}
