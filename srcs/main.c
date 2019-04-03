/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:45:28 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/03 20:46:27 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		main(int ac, char **av)
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
	if (flags.bits.f == 0 && flags.bits.t == 0)
		ft_sort_params(av + num_of_flags + 1);
	else
		ft_sort_balancer(flags, NULL);
	if (flags.bits.upper_r)
	{
		ft_recurcion_flag(av, num_of_flags + 1, flag);
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
