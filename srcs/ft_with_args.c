/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:28:59 by koparker          #+#    #+#             */
/*   Updated: 2019/04/23 17:17:49 by koparker         ###   ########.fr       */
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

void	ft_output_dirs(char *dir_name, t_data *head_dir, int n, t_flags fl)
{
	if (fl.bits.upper_g)
		ft_set_permissions(&head_dir);
	if (n == 1)
		ft_output(head_dir, fl, 1, dir_name);
	else
	{
		ft_putendl(dir_name, 1);
		ft_output(head_dir, fl, 1, dir_name);
	}
}

size_t	ft_process_files(t_data **head, t_flags fl)
{
	DIR		*dirp;
	t_data	*head_file;
	t_data	*tmp;
	size_t	flag;

	flag = 0;
	head_file = NULL;
	dirp = NULL;
	tmp = *head;
	while (tmp)
	{
		if (!(dirp = opendir(tmp->name)) && errno != 13)
			push_back(&head_file, new_file(tmp->name));
		tmp = tmp->next;
	}
	if (head_file != NULL)
	{
		flag = 1;
		if (fl.bits.upper_g)
			ft_set_permissions(&head_file);
		ft_output_files(head_file, fl, 1, (*head)->name);
	}
	return (flag);
}

void	ft_process_dirs(t_data **head, size_t flag, t_flags fl, int n)
{
	DIR		*dirp;
	t_data	*head_dir;
	t_data	*tmp;

	head_dir = NULL;
	tmp = *head;
	while (tmp)
	{
		if ((dirp = opendir(tmp->name)) == NULL)
		{
			if (errno == 13)
				ft_argv_error(tmp->name);
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

void	ft_argv(t_data **head, int n, t_flags fl)
{
	size_t		flag;

	if (fl.bits.d)
	{
		ft_d_flag(*head, fl);
		return ;
	}
	flag = ft_process_files(head, fl);
	ft_process_dirs(head, flag, fl, n);
}
