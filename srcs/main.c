/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 19:45:28 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/03/29 16:28:55 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		main(int ac, char **av)
{
    t_flags flags;
	t_argv	*head;
    int		num_of_flags;

	if (ac == 1)
	{
		ft_without_args(".");
		return (0);
	}
    flags.value = 0;
	num_of_flags = ft_flags(ac, av, flags);
	if (flags.bits.f == 0 && flags.bits.t == 0)
		ft_sort_params(av + num_of_flags + 1);
	head = ft_argv(av + num_of_flags + 1);
	t_argv	*tmp = head;
	while (tmp)
	{
		printf("%s\n", tmp->path_name);
		tmp = tmp->next;
	}
	return (0);
}
