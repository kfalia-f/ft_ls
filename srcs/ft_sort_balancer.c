/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_balanser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:44:26 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/05 22:46:13 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_sort_balancer(t_flags flag, t_data *head)
{
	if (flag.bits.t)
		printf("T\n");
	if (flag.bits.f)
		printf("F\n");
	(void)head;
}

t_data	*ft_balanser_sort(t_data **head, t_flags fl)
{
	t_data	*tmp;

	tmp = *head;
	if (fl.bits.f)
		return (tmp);
//	if (fl.bits.t)
//		ft_lmt_sort(tmp);
//	else
		ft_ascii_sort(&tmp);
	if (fl.bits.r)
		ft_rev_list(&tmp);
	return (tmp);
}
