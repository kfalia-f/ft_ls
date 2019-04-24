/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_balanser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:44:26 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/24 16:55:11 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_balanser_sort(t_data **head, t_flags fl, char *path)
{
	if (fl.bits.f)
		return ;
	if ((fl.bits.t && !fl.bits.l) || (fl.bits.t && !path))
	{
		if (fl.bits.upper_u)
			ft_set_time(head, fl, path);
		else if (fl.bits.u)
			ft_set_time(head, fl, path);
		else
			ft_set_time(head, fl, path);
		ft_ascii_sort(head);
		ft_time_sort(head);
	//	ft_print_list(*head);
	}
	else if (fl.bits.t && fl.bits.l)
	{
		ft_ascii_sort(head);
		ft_time_sort(head);
	}
	else
		ft_ascii_sort(head);
	if (fl.bits.r)
		ft_rev_list(head);
}

void	ft_output(t_data *head, t_flags fl, int to_free, char *path)
{
	ft_balanser_sort(&head, fl, path);
	if (!fl.bits.upper_r)
	{
		if (fl.bits.d)
		{
			if (fl.bits.l && !fl.bits.one)
				ft_simple_l(head, fl);
			else if (!fl.bits.one)
				ft_print(head, fl);
			else
		        ft_print_simple(head, fl);
			ft_free_list(head);
			return ;
		}
	}
	if (fl.bits.l && !fl.bits.one)
		ft_l(path, fl);
	else if (!fl.bits.one)
		ft_print(head, fl);
	else
		ft_print_simple(head, fl);
	if (to_free)
		ft_free_list(head);
}

void	ft_output_files(t_data *head, t_flags fl, int to_free, char *path)
{
	// no need for balanser here, prints files at the top. (already sorted as args)
	if (fl.bits.l && !fl.bits.one)
		ft_l(path, fl);
	else if (!fl.bits.one)
		ft_print(head, fl);
	else
		ft_print_simple(head, fl);
	if (to_free)
		ft_free_list(head);	
}
