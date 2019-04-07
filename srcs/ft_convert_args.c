/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:37:03 by koparker          #+#    #+#             */
/*   Updated: 2019/04/06 16:27:53 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_data	*ft_convert_args(char **av)
{
	t_data	*head;
	size_t	i;

	i = 0;
	head = NULL;
	while (av[i])
		push_back(&head, new_file(av[i++]));
	return (head);
}
