/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:03:17 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/19 17:36:20 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	ft_wrong_flag(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putendl("\nusage: ./ft_ls [-GRUadfglrtu1] [file ...]", 0);
	exit(EXIT_FAILURE);
}

static void	ft_check_flag(char *str, t_flags *flags)
{
	char	*cmp;
	char	*s;
	size_t	i;
	size_t	bits_to_shift;

	i = 1;
	cmp = "GRUadfglrtu1";
	while (str[i])
	{
		if ((s = ft_strchr(cmp, str[i])) != NULL)
			bits_to_shift = s - cmp;
		else
			ft_wrong_flag(str[i]);
		flags->value |= (1 << bits_to_shift);
		i++;
	}
//	if (iisaty(1))
}

int			ft_flags(int ac, char **av, t_flags *flags)
{
	int	i;
	int	num_of_flags;

	i = 1;
	num_of_flags = 0;
	while (i < ac)
	{
		if (av[i][0] == '-' && av[i][1] == '-')
		{
			num_of_flags++;
			if (av[i][2] != '\0')
				ft_wrong_flag('-');
			break ;
		}
		if (av[i][0] == '-')
		{
			ft_check_flag(av[i], flags);
			num_of_flags++;
		}
		else
			break ;
		i++;
	}
	if (flags->bits.g)
		flags->bits.l = 1;
	return (num_of_flags);
}

void	ft_simple_l(t_data *head, t_flags fl)
{
	t_data	*tmp;
	char	*path;

	tmp = head;
	while (head)
	{
		path = ft_str_path(head->name, "/");
		new_l_node(&head, path);
		get_info(path, head, fl);
		head = head->next;
	}
	head = tmp;
	ft_output_info(head, fl);
}

void	ft_d_flag(t_data *head, t_flags fl)
{
	ft_balanser_sort(&head, fl, NULL);
	if (fl.bits.l && !fl.bits.one)
		ft_simple_l(head, fl);
	else if (fl.bits.one == 0)
		ft_print(head);
	else
		ft_print_simple(head);
	ft_free_list(head);
}
