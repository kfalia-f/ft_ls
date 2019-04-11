/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_balanser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:44:26 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/11 18:01:41 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_balanser_sort(t_data **head, t_flags fl)
{
	if (fl.bits.f)
		return ;
	if (fl.bits.t)
		ft_lmt_sort(head);
	else
		ft_ascii_sort(head);
	if (fl.bits.r)
		ft_rev_list(head);
}

void	ft_output(t_data *head, t_flags fl, int to_free)
{
	if (fl.bits.a == 0 && fl.bits.f == 0)
		ft_skip_starting_dots(&head);
	ft_balanser_sort(&head, fl);
	if (fl.bits.one == 0)
		ft_print(head, fl);
	else
		ft_print_simple(&head, fl);
	if (to_free)
		ft_free_list(head);
}
