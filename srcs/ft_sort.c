/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:03:30 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/17 17:37:42 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	split_list(t_data *head, t_data **first_half, t_data **second_half)
{
	t_data	*ptr1;
	t_data	*ptr2;

	ptr1 = head;
	ptr2 = head->next;
	while (ptr2)
	{
		ptr2 = ptr2->next;
		if (ptr2)
		{
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
	}
	*first_half = head;
	*second_half = ptr1->next;
	ptr1->next = NULL;
}

t_data	*merge_ascii(t_data *a, t_data *b)
{
	t_data	*res;

	res = NULL;
	if (!a)
		return (b);
	else if (!b)
		return (a);
	if (ft_strcmp(a->name, b->name) < 0)
	{
		res = a;
		res->next = merge_ascii(a->next, b);
	}
	else
	{
		res = b;
		res->next = merge_ascii(a, b->next);
	}
	return (res);
}

void	ft_ascii_sort(t_data **head)
{
	t_data	*tmp;
	t_data	*first_half;
	t_data	*second_half;

	tmp = *head;
	if (!tmp || !(tmp->next))
		return ;
	split_list(tmp, &first_half, &second_half);
	ft_ascii_sort(&first_half);
	ft_ascii_sort(&second_half);
	*head = merge_ascii(first_half, second_half);
}

t_data	*merge_time(t_data *a, t_data *b)
{
	t_data	*res;

	res = NULL;
	if (!a)
		return (b);
	else if (!b)
		return (a);
	if (a->time >= b->time)
	{
		res = a;
		res->next = merge_time(a->next, b);
	}
	else
	{
		res = b;
		res->next = merge_time(a, b->next);
	}
	return (res);
}

void	ft_time_sort(t_data **head)
{
	t_data	*tmp;
	t_data	*first_half;
	t_data	*second_half;

	tmp = *head;
	if (!tmp || !(tmp->next))
		return ;
	split_list(tmp, &first_half, &second_half);
	ft_time_sort(&first_half);
	ft_time_sort(&second_half);
	*head = merge_time(first_half, second_half);
}
