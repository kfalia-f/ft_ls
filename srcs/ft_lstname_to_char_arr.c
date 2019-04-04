/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstname_to_char_arr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:33:28 by koparker          #+#    #+#             */
/*   Updated: 2019/04/04 15:54:56 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char	**ft_lstname_to_char_arr(char **arr, t_data *data)
{
	t_data	*tmp;
	int		i;

	i = 0;
	tmp = data;
	while (tmp != NULL)
	{
		arr[i] = ft_strcpy(arr[i], tmp->name);
		i++;
		tmp = tmp->next;
	}
	return (arr);
}
