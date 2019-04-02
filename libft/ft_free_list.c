/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:27:58 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/02 17:33:56 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_free_list(t_data *head)
{
	t_data	*tmp;

	if (head == NULL)
		return ;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
	}
}
