/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_balanser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:44:26 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/14 00:21:07 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_balanser_sort(t_data **head, t_flags fl)
{
	if (fl.bits.f)
		return ;
	if (fl.bits.t == 1)
	{
		if (fl.bits.upper_u == 1)
			ft_set_time(head, fl);
		else if (fl.bits.u == 1)
			ft_set_time(head, fl);
		else
			ft_set_time(head, fl);
		ft_ascii_sort(head);
		ft_time_sort(head);
	}
	else
		ft_ascii_sort(head);
	if (fl.bits.r)
		ft_rev_list(head);
}

void	ft_output(t_data *head, t_flags fl, int to_free)
{
	if (fl.bits.a == 0 && fl.bits.f == 0)
		ft_remove_dots(&head);
	ft_balanser_sort(&head, fl);
	if (fl.bits.one == 0)
		ft_print(head);
	else
		ft_print_simple(&head);
	if (to_free)
		ft_free_list(head);
}
