/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:28:59 by koparker          #+#    #+#             */
/*   Updated: 2019/04/02 19:41:29 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_data	*ft_readdir(DIR *dirp)
{
	struct dirent	*dp;
	t_data			*head;

	head = NULL;
	while ((dp = readdir(dirp)) != NULL)
		push_back(&head, new_node(dp));
	return (head);
}

void	ft_nonexistent_argv_error(char *name)
{
	ft_putstr("ft_ls: ");
	ft_putstr(name);
	ft_putstr(": ");
	ft_putstr(strerror(errno));
	ft_putchar('\n');
}

void	ft_output_dirs(t_data *head, int n)
{
	t_data	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (n == 1)
			ft_print(ft_ascii_sort(&tmp));
		else
		{
			ft_putendl(tmp->name, 1);
			ft_print(ft_ascii_sort(&tmp));
			if (tmp->next->name != NULL)
				ft_putchar('\n');
		}
		tmp = tmp->next;
	}
}

void	ft_argv(char **av, int n)
{
	DIR			*dirp;
	t_data		*head_file;
	t_data		*head_dir;
	int			i;

	i = 0;
	head_file = NULL;
	head_dir = NULL;
	while (av[i] != NULL)
	{
		if ((dirp = opendir(av[i])) == NULL)
		{
    		if (errno != 20)
    			ft_nonexistent_argv_error(av[i]);
    		else
    		{
    			push_back(&head_file, new_file(av[i]));
    		}
    	}
    	i++;
    }
	ft_print(head_file);
	i = 0;
	while (av[i] != NULL)
	{
		if ((dirp = opendir(av[i])) == NULL)
		{
			i++;
			continue ;
		}
		push_back(&head_dir, ft_readdir(dirp));
		closedir(dirp);
		ft_output_dirs(head_dir, n);
		head_dir = NULL;
		i++;
	}
}
