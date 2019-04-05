/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:45:28 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/05 22:46:53 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_print_current(t_data *head, t_flags fl)
{
	t_data	*tmp;

	tmp = head;
	if (fl.bits.a == 0 && fl.bits.f == 0)
	{
		while ((*tmp->name) == '.')
			tmp = tmp->next;
	}
	while (tmp)
	{
		if (fl.bits.r == 1 && (*tmp->name) == '.')
			break ;
		ft_putendl(tmp->name, 0);
		tmp = tmp->next;
	}
}

void	process_current_dir(char *s, t_flags fl)
{
	t_data	*head;

	head = ft_current_dir(s);
	head = ft_balanser_sort(&head, fl);
	if (fl.bits.one == 1)
		ft_print_current(head, fl);
	//modified versin of ft_without_args(s);
}

int	main(int ac, char **av)
{
	t_flags flags;
	int		num_of_flags;
	int		flag;

	if (ac == 1)
	{
		ft_without_args(".");
		return (0);
	}
	flags.value = 0;
	num_of_flags = ft_flags(ac, av, &flags);
	flag = ac - num_of_flags - 1;
	if (flag == 0)
		process_current_dir(".", flags);
	ft_sort_params(av + num_of_flags + 1, num_of_flags, flags);
/*	
	if (flags.bits.f == 0 && flags.bits.t == 0)
		ft_sort_params(av + num_of_flags + 1);
	else
		ft_sort_balancer(num_of_flags, flags, NULL);
*/	if (flags.bits.upper_r)
	{
		ft_recurcion_flag(av, num_of_flags + 1, flag, flags);
		return (0);
	}
	if (flags.bits.l)
	{
		ft_l_flag(av, num_of_flags + 1, flag, flags);
		return (0);
	}
	ft_argv(av + num_of_flags + 1, ac - num_of_flags - 1, flags);
	return (0);
}
