/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:23:54 by koparker          #+#    #+#             */
/*   Updated: 2019/04/28 17:51:52 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		ft_timecmp(long a, long b)
{
	if (a >= b)
		return (0);
	return (1);
}

void	ft_del_perms(char **perms, size_t list_size, t_data *head)
{
	ft_del(&perms, list_size);
	ft_free_perm(&head);
}
