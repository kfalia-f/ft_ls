/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:24:54 by koparker          #+#    #+#             */
/*   Updated: 2019/03/26 19:06:44 by kfalia-f         ###   ########.fr       */
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

size_t  ft_lstsize(t_data *lst)
{
	size_t  i;
	t_data  *tmp;

	i = 0;
	tmp = lst;
	if (lst == NULL)
		return (0);
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
