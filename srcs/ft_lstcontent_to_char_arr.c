/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcontent_to_char_arr.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:33:28 by koparker          #+#    #+#             */
/*   Updated: 2019/04/26 15:58:30 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_lstcontent_to_char_arr(char **arr, t_data *data, size_t flag)
{
	t_data	*tmp;
	int		i;

	i = 0;
	tmp = data;
	while (tmp != NULL)
	{
		if (flag == 0)
			arr[i] = ft_strcpy(arr[i], tmp->name);
		else
			arr[i] = ft_strcpy(arr[i], tmp->perm);
		i++;
		tmp = tmp->next;
	}
}
