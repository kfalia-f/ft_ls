/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_balanser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:44:26 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/11 17:58:23 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_data	*ft_balanser_sort(t_data **head, t_flags fl)
{
	t_data	*tmp;

	tmp = *head;
	if (fl.bits.f)
		return (tmp);
	if (fl.bits.t)
		ft_lmt_sort(&tmp);
	else
		ft_ascii_sort(&tmp);
	if (fl.bits.r)
		ft_rev_list(&tmp);
	return (tmp);
}

void	ft_output(t_data *head, t_flags fl, int to_free)
{
	t_data	*tmp;

	tmp = head;
	tmp = ft_balanser_sort(&tmp, fl);
	ft_print(tmp, fl);
	if (to_free)
		ft_free_list(tmp);
}
