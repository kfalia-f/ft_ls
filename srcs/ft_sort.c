/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:03:30 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/03/24 15:29:16 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_data	*ft_ascii_sort(t_data **head)
{
	t_data	*tmp;
	char	*strtmp;

	tmp = *head;
	while ((*head)->next)
	{
		if (ft_strcmp((*head)->name, (*head)->next->name) > 0)
		{
			strtmp = (*head)->name;
			(*head)->name = (*head)->next->name;
			(*head)->next->name = strtmp;
			*head = tmp;
		}
		else
			(*head) = (*head)->next;
	}
	*head = tmp;
	return (*head);
}

// prototype of a balanser function of various sort algs for flags for example
// void	ft_sort(t_argv *head, t_flags flag);
