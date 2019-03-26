/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 21:43:49 by koparker          #+#    #+#             */
/*   Updated: 2019/03/25 18:09:13 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define TRUE_LS 1

# include <dirent.h>
# include <libft.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
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
	unsigned char   len;
}                   t_data;

typedef struct      s_argv
{
	struct s_argv   *next;
	struct s_data   *data;
	char            *path_name;
	unsigned char   len;
}                   t_argv;

void				ft_without_args(char *str);
t_data				*new_node(struct dirent *dp);
void				push_back(t_data **head, t_data *node);
t_argv				*new_argv(char *str);
void				push_back_argv(t_argv **head, t_argv *node);
t_data				*ft_ascii_sort(t_data **head);
int					ft_max_namlen(t_data *data);
void				ft_output_spaces(char c, int len);
#endif
