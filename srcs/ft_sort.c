/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:03:30 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/11 17:25:50 by kfalia-f         ###   ########.fr       */
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

t_lflag	*ft_l_ascii_sort(t_lflag **head)
{
	t_lflag	**prev;
	t_lflag	*curr;
	t_lflag	*next;
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
			if (ft_strcmp(curr->file_name, next->file_name) > 0)
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

t_data	*ft_lmt_sort(t_data **head)
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
			if (curr->time < next->time)
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
