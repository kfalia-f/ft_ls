/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:28:59 by koparker          #+#    #+#             */
/*   Updated: 2019/04/07 21:11:39 by koparker         ###   ########.fr       */
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

void	ft_push_file(char *name, DIR *dirp, t_data **head_file)
{
	if ((dirp = opendir(name)) == NULL)
	{
		if (errno != 20)
			ft_nonexistent_argv_error(name);
		else
			push_back(head_file, new_file(name));
	}
}

size_t	ft_process_flags(t_data **head, DIR *dirp, t_flags fl)
{
	t_data	*head_file;
	t_data	*tmp;
	size_t	flag;

	flag = 0;	
	head_file = NULL;
	tmp = *head;
	while (tmp)
	{
		ft_push_file(tmp->name, dirp, &head_file);
		tmp = tmp->next;
	}
	if (head_file != NULL)
	{
		flag = 1;
		ft_print(head_file, fl);
		ft_free_list(head_file);
	}
	return (flag);
}

void	ft_argv(t_data **head, int n, t_flags fl)
{
	DIR			*dirp;
	t_data		*head_dir;
	t_data		*tmp;
	size_t		flag;

	head_dir = NULL;
	dirp = NULL;
	flag = ft_process_flags(head, dirp, fl);
	tmp = *head;
	while (tmp)
	{
		if ((dirp = opendir(tmp->name)) == NULL)
		{
			tmp = tmp->next;
			continue ;
		}
		head_dir = ft_readdir(dirp);
		closedir(dirp);
		if (flag == 1)
		{
			flag = 2;
			ft_putchar('\n');
		}
		ft_output_dirs(tmp->name, head_dir, n, fl);
		ft_putchar('\n');
		ft_free_list(head_dir);
		tmp = tmp->next;
	}
}
