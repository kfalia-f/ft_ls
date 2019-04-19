/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 21:43:49 by koparker          #+#    #+#             */
/*   Updated: 2019/04/19 13:42:47 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define TRUE_LS 1
# define TAB 8

# include <dirent.h>
# include <libft.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <unistd.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <stdio.h>

typedef struct		s_bits
{
	unsigned int	upper_g : 1;
	unsigned int	upper_r : 1;
	unsigned int	upper_u : 1;
	unsigned int	a : 1;
	unsigned int	d : 1;
	unsigned int	f : 1;
	unsigned int	g : 1;
	unsigned int	l : 1;
	unsigned int	r : 1;
	unsigned int	t : 1;
	unsigned int	u : 1;
	unsigned int	one : 1;
}					t_bits;

typedef union		u_flags
{
	unsigned int	value;
	struct s_bits	bits;
}					t_flags;

typedef struct		s_lflag
{
	size_t			file_size;
	size_t			links;
	size_t			total;
	size_t			maj;
	size_t			min;
	char			*permissions;
	char			*owner;
	char			*group;
	char			*date;
	char			*file_name;
	char			*link;
}					t_lflag;

typedef struct		s_data
{
	struct s_data	*next;
	struct s_lflag	*l_info;
	char			*name;
	size_t			len;
	long			time;
}					t_data;

char				**ft_lstname_to_str_arr(char **arr, t_data *data);
void				ft_window(t_data *data);
t_data				*new_node(struct dirent *dp);
t_data				*new_file(char *str);
void				push_back(t_data **head, t_data *node);
size_t				ft_list_size(t_data *lst);
void				ft_rev_list(t_data **head);
void				ft_free_list(t_data *head);

t_lflag				*ft_l_ascii_sort(t_lflag **head);

size_t				ft_max_namlen(t_data *data);
void				ft_output_spaces(char c, size_t len);
int					ft_flags(int ac, char **av, t_flags *flags);
void				ft_sort_params(char **av, int num_of_flags, t_flags fl);
void				ft_argv(t_data **head, int n, t_flags fl);

void				ft_recursion_flag(char **av, int flag, t_flags flags);
void				ft_l_flag(t_data *av, int flag, t_flags flags);

char				**ft_lstname_to_char_arr(char **arr, t_data *data);
t_data				*ft_readdir(DIR *dirp, t_flags fl);
void				ft_print(t_data *head);

int					ft_timecmp(long a, long b);
void				ft_time_sort(t_data **head);
void				ft_ascii_sort(t_data **head);
void				ft_balanser_sort(t_data **head, t_flags fl, char *path);
t_data				*ft_current_dir(char *s, t_flags fl);
void				ft_set_time(t_data **head, t_flags fl, char *path);
void				ft_remove_dots(t_data **head);
t_data				*ft_convert_args(char **av);
void				ft_print_simple(t_data *head);
void				ft_skip_dots(t_data **head, t_flags fl);
void				ft_process_current_dir(char *s, t_flags fl);
void				ft_output(t_data *head, t_flags fl, int to_free, char *path);
void				ft_output_files(t_data *head, t_flags fl, int to_free, char *path);

void				l_push_back(t_lflag **head, t_lflag *node);
void				new_l_node(t_data **av, char *path);
void				ft_l(char *path_name, t_flags fl);
t_data				*ft_convert_args(char **av);
void				ft_simple_l(t_data *head, t_flags fl);

void				ft_link(t_data *av, char *path, int flag, t_flags fl);
void				get_info(char *path, t_data *st, t_flags fl);
void				ft_output_info(t_data *st, t_flags fl);

void				ft_d_flag(t_data *head, t_flags fl);
void				ft_balanser_sort(t_data **head, t_flags fl, char *path);

void				ft_argv_error(char *s);

void				ft_print_list(t_data *head);
#endif
