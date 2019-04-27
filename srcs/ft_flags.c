/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <kfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:03:17 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/27 15:48:34 by kfalia-f         ###   ########.fr       */
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

	i = 0;
	num_of_flags = 0;
	while (++i < ac)
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
	}
	if (flags->bits.g)
		flags->bits.l = 1;
	return (num_of_flags);
}

void		ft_simple_l(t_data *head, t_flags fl)
{
	t_data	*tmp;

	tmp = head;
	while (head)
	{
		new_l_node(&head, head->name, fl);
		get_info(head->name, head, fl);
		head = head->next;
	}
	head = tmp;
	ft_output_info(head, fl);
	ft_free_list(&tmp, 1);
}

void		ft_d_flag(t_data *head, t_flags fl)
{
	ft_balanser_sort(&head, fl, NULL);
	if (fl.bits.l && !fl.bits.one)
		ft_simple_l(head, fl);
	else if (!fl.bits.one)
	{
		if (fl.bits.upper_g)
			ft_set_permissions(&head, NULL);
		ft_print(head, fl);
	}
	else
		ft_print_simple(head, fl);
	if (!fl.bits.l)
		ft_free_list(&head, 0);
}
