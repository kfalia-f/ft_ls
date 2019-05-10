/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <kfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 21:43:49 by koparker          #+#    #+#             */
/*   Updated: 2019/05/10 17:50:33 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define TAB	8
# define RESET	"\x1B[0m"
# define EXE_COLOR	"\x1B[31m"
# define DIR_COLOR	"\x1B[34m"
# define SIMLNK_BASE_COLOR	"\x1B[35m"
# define BLOCK_COLOR	"\x1B[34m\x1B[46m"
# define CHAR_COLOR	"\x1B[34m\x1B[43m"
# define EXE_SETUID_COLOR	"\x1B[30m\x1B[41m"
# define EXE_SETGID_COLOR	"\x1B[30m\x1B[46m"
# define STICKY_BIT_COLOR	"\x1B[30m\x1B[42m"
# define NO_STICKY_BIT_COLOR	"\x1B[30m\x1B[43m"
# define PERM_SIZE	12

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
	char			*perm;
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
	char			*perm;
	size_t			len;
	long			time;
}					t_data;

void				ft_lstcontent_to_char_arr(char **arr, t_data *data,
					size_t flag);
t_data				*new_node(struct dirent *dp);
t_data				*new_file(char *str);
void				push_back(t_data **head, t_data *node);
size_t				ft_list_size(t_data *lst);
void				ft_rev_list(t_data **head);
void				ft_free_list(t_data **head, size_t flag_l);
void				ft_free_perm(t_data **head);

size_t				ft_max_namlen(t_data *data);
void				ft_output_spaces(char c, size_t len);
int					ft_flags(int ac, char **av, t_flags *flags);
void				ft_argv(t_data **head, int n, t_flags fl);

void				ft_recursion_flag(t_data *av, int flag, t_flags flags);
int					ft_dot(t_data *head, t_flags fl, int i, int flag);
void				ft_l_flag(t_data *av, int flag, t_flags flags);

t_data				*ft_readdir(DIR *dirp, char *path, t_flags fl);
void				ft_print(t_data *head, t_flags fl, char *path);
void				ft_print_first_upper_g(char **names, char **perms,
					size_t row);
void				ft_pr_upper_g(char **names, char **perms, size_t row,
					size_t max_len);

int					ft_timecmp(long a, long b);
void				ft_time_sort(t_data **head);
void				ft_ascii_sort(t_data **head);
void				ft_balanser_sort(t_data **head, t_flags fl, char *path);
t_data				*ft_current_dir(char *s, t_flags fl);
void				ft_set_time(t_data **head, t_flags fl, char *path);
void				ft_remove_dots(t_data **head);
t_data				*ft_convert_args(char **av);
void				ft_print_simple(t_data *head, t_flags fl);
void				ft_print_simple_colorized(t_data *head);
void				ft_process_current_dir(char *s, t_flags fl);
void				ft_output(t_data *head, t_flags fl, int to_free,
					char *path);
void				ft_output_files(t_data *head, t_flags fl, int to_free,
					char *path);

void				l_push_back(t_lflag **head, t_lflag *node);
void				new_l_node(t_data **av, char *path, t_flags fl);
void				ft_l(char *path_name, t_flags fl);
t_data				*ft_convert_args(char **av);
void				ft_simple_l(t_data *head, t_flags fl);

void				time_balanser_get_info(t_data *st, t_flags fl,
					struct stat buff);
char				*ft_date(char *data, size_t tm, int i, int j);
void				ft_link(t_data *av, char *path);
void				get_info(char *path, t_data *st, t_flags fl);
void				ft_output_info(t_data *st, t_flags fl);
void				ft_arr(t_data *st, int a[6]);
int					ft_max_llen(t_data *st, int flag);
int					ft_len(size_t n);
void				ft_sps(char *str, size_t len);

void				ft_d_flag(t_data *head, t_flags fl);
void				ft_balanser_sort(t_data **head, t_flags fl, char *path);

void				ft_argv_error(char *s);
void				ft_colorized_output_l(char *perm, char *name);
void				ft_colorized_output(char *perm, char *name);
char				*get_permission(mode_t st_mode, char *path);
void				ft_set_permissions(t_data **head, char *path);

void				ft_recurs(char *path_name, DIR *dirp, t_flags fl);

void				ft_process_dirs_helper(size_t *flag);
void				ft_del_perms(char **perms, size_t list_size, t_data *head);
#endif
