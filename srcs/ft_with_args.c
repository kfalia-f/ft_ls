/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:28:59 by koparker          #+#    #+#             */
/*   Updated: 2019/04/03 18:19:38 by koparker         ###   ########.fr       */
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

void	ft_output_dirs(char *dir_name, t_data *head, int n, t_flags fl)
{
	if (n == 1)
		ft_print(ft_ascii_sort(&head), fl);
	else
	{
		ft_putendl(dir_name, 1);
		ft_print(ft_ascii_sort(&head), fl);
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
//	(void)n;
	t_flags	fl;
	char	*s;
	s = "";
	fl.value = 0;
	int num_of_flags = ft_flags(1, &s, fl);
	num_of_flags = 0;
	if (head_file != NULL)
		ft_print(head_file, fl);
	i = 0;
	while (av[i] != NULL)
	{
		if ((dirp = opendir(av[i])) == NULL)
		{
			i++;
			continue ;
		}
		head_dir = ft_readdir(dirp);
		closedir(dirp);
		ft_output_dirs(av[i], head_dir, n, fl);
		if (av[i +1] != NULL)
			ft_putchar('\n');
		ft_free_list(head_dir);
		i++;
	}
}
