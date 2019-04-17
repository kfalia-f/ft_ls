/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:45:28 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/17 15:05:52 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		main(int ac, char **av)
{
	t_data	*args;
    t_flags fl;
    int		num_of_flags;
	int		flag;

    fl.value = 0;
	num_of_flags = ft_flags(ac, av, &fl);
	flag = ac - num_of_flags - 1;
	args = ft_convert_args(av + num_of_flags + 1);
/*	while (1)
	{
		if (fl.bits.upper_r == 1)
			ft_putendl("R", 0);
		if (fl.bits.upper_g == 1)
			ft_putendl("G", 0);
		if (fl.bits.a == 1)
			ft_putendl("a", 0);
		if (fl.bits.f == 1)
			ft_putendl("f", 0);
		if (fl.bits.l == 1)
			ft_putendl("l", 0);
		if (fl.bits.r == 1)
			ft_putendl("r", 0);
		if (fl.bits.t == 1)
			ft_putendl("t", 0);
		if (fl.bits.u == 1)
			ft_putendl("u", 0);
		if (fl.bits.one == 1)
			ft_putendl("1", 0);
		break ;
	}*/
	if (flag == 0 && fl.bits.upper_r == 0)
	{
		ft_process_current_dir(".", fl);
		return (0);
	}
	if (fl.bits.d)
	{
		ft_argv(&args, ac - num_of_flags - 1, fl);
		return (0);
	}
	ft_balanser_sort(&args, fl, NULL);
	if (fl.bits.l && fl.bits.upper_r == 0)
		ft_l_flag(av, num_of_flags + 1, flag, fl);
	if (fl.bits.upper_r)
		ft_recursion_flag(av + num_of_flags + 1, flag, fl);
	else
		ft_argv(&args, ac - num_of_flags - 1, fl);
	return (0);
}
