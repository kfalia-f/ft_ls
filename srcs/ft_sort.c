/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:03:30 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/03/25 18:09:22 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_data	*ft_ascii_sort(t_data **head)
{
	t_data	**prev;
	t_data	*curr;
	t_data	*next;
	int		done;

	done = 0;
	if (*head == NULL || (*head)->next == NULL)
		return (NULL);
	while (!done)
	{
		prev = head;
		curr = *head;
		next = (*head)->next;
		done = 1;
		while (next)
		{
			if (ft_strcmp(curr->name, next->name) > 0)
			{
				curr->next = next->next;
				next->next = curr;
				*prev = next;
				done = 0;
			}
			prev = &curr->next;
			curr = next;
			next = next->next;
		}
	}
	return (*head);
}

// prototype of a balanser function of various sort algs for flags for example
// void	ft_sort(t_argv *head, t_flags flag);
