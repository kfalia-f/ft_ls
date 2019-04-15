/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:28:59 by koparker          #+#    #+#             */
/*   Updated: 2019/04/15 16:16:53 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_data	*ft_readdir(DIR *dirp, t_flags fl)
{
	struct dirent	*dp;
	t_data			*head;

	head = NULL;
	while ((dp = readdir(dirp)) != NULL)
	{
		if (*(dp->d_name) == '.')
			if (!fl.bits.a && !fl.bits.f)
				continue ;
		push_back(&head, new_node(dp));
	}
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

void	ft_output_dirs(char *dir_name, t_data *head_dir, int n, t_flags fl)
{
	if (n == 1)
		ft_output(head_dir, fl, 1, NULL);
	else
	{
		ft_putendl(dir_name, 1);
		ft_output(head_dir, fl, 1, NULL);
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
		ft_output(head_file, fl, 1, NULL);
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
		head_dir = ft_readdir(dirp, fl);
		closedir(dirp);
		if (flag == 1)
		{
			flag = 2;
			ft_putchar('\n');
		}
		ft_output_dirs(tmp->name, head_dir, n, fl);
		tmp = tmp->next;
		if (tmp)
			ft_putchar('\n');
	}
}
