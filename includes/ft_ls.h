/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 21:43:49 by koparker          #+#    #+#             */
/*   Updated: 2019/04/05 22:29:54 by koparker         ###   ########.fr       */
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

# include <stdio.h>

typedef struct		s_bits
{
	unsigned int	upper_r : 1;
	unsigned int	a : 1;
	unsigned int	f : 1;
	unsigned int	l : 1;
	unsigned int	r : 1;
	unsigned int	t : 1;
	unsigned int	one : 1;
}					t_bits;

typedef union		u_flags
{
	unsigned int	value;
	struct s_bits	bits;
}					t_flags;

typedef struct      s_data
{
	struct s_data   *next;
	char            *name;
	size_t			len;
	long			time;
}                   t_data;

char				**ft_lstname_to_str_arr(char **arr, t_data *data);
void				ft_output(char **arr, size_t row, size_t list_size, size_t max_namlen);
void				ft_window(t_data *data);
void				ft_without_args(char *str);
t_data				*new_node(struct dirent *dp);
t_data				*new_file(char *str);
void				push_back(t_data **head, t_data *node);
void				ft_rev_list(t_data **head);
void				ft_free_list(t_data *head);

t_data				*ft_ascii_sort(t_data **head);
size_t				ft_max_namlen(t_data *data);
void				ft_output_spaces(char c, size_t len);
size_t				ft_list_size(t_data *lst);
int					ft_flags(int ac, char **av, t_flags *flags);
void				ft_sort_params(char **av, int num_of_flags, t_flags fl);
void				ft_argv(char **av, int n, t_flags fl);

void				ft_sort_balancer(t_flags flag, t_data *head);
void				ft_recurcion_flag(char **av, int i, int flag, t_flags flags);
void				ft_l_flag(char **av, int i, int flag, t_flags flags);

char				**ft_lstname_to_char_arr(char **arr, t_data *data);
t_data				*ft_readdir(DIR *dirp);
void				ft_print_without_args(t_data *head);
void				ft_print(t_data *head, t_flags fl);

int					ft_mtimecmp(long a, long b);
t_data				*ft_lmt_sort(t_data **head, t_flags fl);
t_data				*ft_balanser_sort(t_data **head, t_flags fl);
t_data				*ft_current_dir(char *s);
#endif
