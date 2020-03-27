#include <ft_ls.h>

t_data	*ft_readdir(DIR *dirp, char *path, t_flags fl)
{
	struct dirent	*dp;
	struct stat		buff;
	t_data			*head;
	char			*pt;

	head = NULL;
	while ((dp = readdir(dirp)) != NULL)
	{
		if (*(dp->d_name) == '.')
			if (!fl.bits.a && !fl.bits.f)
				continue ;
		pt = ft_str_path(path, dp->d_name);
		if (lstat(pt, &buff) >= 0)
			push_back(&head, new_node(dp));
		free(pt);
	}
	return (head);
}

void	ft_output_dirs(char *dir_name, t_data *head_dir, int n, t_flags fl)
{
	if (fl.bits.upper_g)
		ft_set_permissions(&head_dir, dir_name);
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
		if ((dirp = opendir(tmp->name)) == NULL && errno != 13)
			push_back(&head_file, new_file(tmp->name));
		tmp = tmp->next;
		if (dirp != NULL)
			closedir(dirp);
	}
	if (head_file != NULL)
	{
		flag = 1;
		if (fl.bits.upper_g)
			ft_set_permissions(&head_file, NULL);
		ft_output_files(head_file, fl, 1, (*head)->name);
	}
	return (flag);
}

/*
** With errors there are 3 cases:
** 1: there are no files before Permission denied for dirs
** 2: there are files -//- (case: flag + 2)
** 3: there are dirs after Permission denied for dirs
*/

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
				(tmp->next) ? ft_argv_error(tmp->name, flag) :
				ft_argv_error(tmp->name, flag + 2);
			tmp = tmp->next;
			continue ;
		}
		head_dir = ft_readdir(dirp, tmp->name, fl);
		closedir(dirp);
		if (flag != 0)
			ft_process_dirs_helper(&flag);
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
