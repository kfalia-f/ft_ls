/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:45:28 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/05/14 18:34:24 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_with_args_main(t_data *args, size_t n_of_fl, t_flags fl)
{
	ft_argv(&args, n_of_fl, fl);
	if (!fl.bits.d)
		ft_free_list(&args, 0);
}

int		main(int ac, char **av)
{
	t_data	*args;
	t_flags	fl;
	int		num_of_flags;
	int		flag;

	fl.value = 0;
	num_of_flags = ft_flags(ac, av, &fl);
	flag = ac - num_of_flags - 1;
	if (fl.bits.d)
		fl.bits.upper_r = 0;
	if (!flag && !fl.bits.upper_r)
	{
		ft_process_current_dir(".", fl);
		return (0);
	}
	args = ft_convert_args(av + num_of_flags + 1);
	if (args)
		ft_balanser_sort(&args, fl, NULL);
	if (fl.bits.l && !fl.bits.upper_r && !fl.bits.d)
		ft_l_flag(args, flag, fl);
	else if (fl.bits.upper_r)
		ft_recursion_flag(args, flag, fl);
	else
		ft_with_args_main(args, ac - num_of_flags - 1, fl);
	return (0);
}
