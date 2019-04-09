/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:24:54 by koparker          #+#    #+#             */
/*   Updated: 2019/04/09 17:32:24 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

size_t	ft_max_namlen(t_data *data)
{
	t_data	*tmp;
	size_t	max;

	if (data == NULL)
		return (0);
	tmp = data;
	max = tmp->len;
	while (tmp)
	{
		if (max < tmp->len)
			max = tmp->len;
		tmp = tmp->next;
	}
	return (max);
}

void	ft_output_spaces(char c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		ft_putchar(c);
		i++;
	}
}

void	ft_skip_dots(t_data **head)
{
	if ((*((*head)->name) == '.') && (*head)->len == 1)
		*head = (*head)->next;
	if (ft_strcmp((*head)->name, "..") == 0 && (*head)->len == 2)
		*head = (*head)->next;
}

void	ft_skip_starting_dots(t_data **head)
{
//	t_data	*tmp;

	while ((*(*head)->name) == '.')
	{
//		tmp = *head;
		*head = (*head)->next;
//		free(tmp);
//		tmp = NULL;
	}
}
