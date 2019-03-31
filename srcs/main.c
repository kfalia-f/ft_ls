/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:45:28 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/03/31 19:41:14 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		main(int ac, char **av)
{
    t_flags flags;
    int		num_of_flags;

	if (ac == 1)
	{
		ft_without_args(".");
		return (0);
	}
    flags.value = 0;
	num_of_flags = ft_flags(ac, av, &flags);
	if (flags.bits.f == 0 && flags.bits.t == 0)
		ft_sort_params(av + num_of_flags + 1);
	ft_argv(av + num_of_flags + 1, ac - num_of_flags - 1);
	return (0);
}
