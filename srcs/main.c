/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:45:28 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/03/28 15:53:01 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		main(int ac, char **av)
{
    t_flags flags;
    size_t  flags_offset;

	if (ac == 1)
	{
		ft_without_args(".");
		return (0);
	}
    flags.value = 0;
	flags_offset = ft_flags(ac, av, flags);
	return (0);
}
