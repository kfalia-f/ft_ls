/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argvlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:30:25 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/03/24 14:32:11 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_argv	*new_argv(char *str)
{
	t_argv  *node;

	if (!(node = (t_argv *)malloc(sizeof(t_argv))))
	{
		ft_putendl("doesn't malloced for argv node", 0);
		return (NULL);
	}
	node->path_name = str;
	node->next = NULL;
	return (node);
}

void    push_back_argv(t_argv **head, t_argv *node)
{
	t_argv  *tmp;

	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}
