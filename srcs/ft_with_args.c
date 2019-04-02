/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:28:59 by koparker          #+#    #+#             */
/*   Updated: 2019/03/31 22:34:50 by koparker         ###   ########.fr       */
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

// read argv
/*t_holder	*ft_read_data(char *str)
{
	// opendir, read data, closedir. Output error OR Store errors
	DIR				*dirp;
	t_data			*head_file;
	t_data			*head_dir;
	t_holder		*holder;

	// TODO: I set heads to NULL every time, so only the last elemen of the corresponding list
	// exist at the time of printing !!!!!!!!!!!!!!!!
	head_file = NULL;
	head_dir = NULL;
	push_back(&head_file, new_file("-1"));
	holder = new_elem(head_file);
	if (!(dirp = opendir(str)))
	{
		// use 'stat' to obtain info dir OR file (not errno code)
		if (errno != 20)
			ft_nonexistent_argv_error(str);
		else
		{
			push_back(&head_file, new_file(str));
			holder = new_elem(head_file);
			return (holder);
			// node who accepts char *, but doesn't need dp
		}
		return (NULL);
	}
	head_dir = ft_readdir(dirp);
	holder->next = new_elem(head_dir);
	closedir(dirp);
	return (holder);
}*/

void	ft_output_files(t_data *head)
{
	t_data	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
//		if (ft_strcmp(tmp->name, "-1") == 0)
//			tmp = tmp->next;
		ft_window(ft_ascii_sort(&tmp));
		tmp = tmp->next;
	}
}

void	ft_output_dirs(t_data *head, int n)
{
	t_data	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (n == 1)
			ft_window(ft_ascii_sort(&tmp));
		else
		{
			ft_putendl(tmp->name, 1);
			ft_window(ft_ascii_sort(&tmp));
			if (tmp->next->name != NULL)
				ft_putchar('\n');
		}
		tmp = tmp->next;
	}
}

// fill external list
void	ft_argv(char **av, int n)
{
	DIR			*dirp;
	t_data		*head_file;
	t_data		*head_dir;
	int			i;

	i = 0;
	head_file = NULL;
	head_dir = NULL;
//	push_back(&head_file, new_file("-1"));
	while (av[i] != NULL)
	{
    	if (!(dirp = opendir(av[i])))
    	{
    		if (errno != 20)
    			ft_nonexistent_argv_error(av[i]);
    		else
    		{
    			push_back(&head_file, new_file(av[i]));
    		}
    	}
    	else
        {
            push_back(&head_dir, ft_readdir(dirp));
    	    closedir(dirp);
        }
    	i++;
    }
    // TODO: ft_window() is corrupted.
    (void)n;
    t_data	*file = head_file;;
	while (file != NULL)
	{
		printf("%s\n", file->name);
		file = file->next;
	}
	/*while (dir != NULL)
	{
		printf("%s\n", dir->name);
		dir = dir->next;		
	}*/
//	ft_output_files(head_file);
//	ft_output_dirs(head_dir, n);
}
