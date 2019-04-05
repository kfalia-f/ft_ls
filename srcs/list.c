/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:27:53 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/05 22:38:22 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_data	*new_node(struct dirent *dp)
{
	t_data	*node;

	if (!(node = (t_data *)malloc(sizeof(t_data))))
	{
		ft_putendl("doesn't malloced for a new node", 0);
		return (NULL);
	}
	node->name = dp->d_name;
	node->len = ft_strlen(node->name);
	node->next = NULL;
	return (node);
}

t_data	*new_file(char *str)
{
	t_data	*node;

	if (!(node = (t_data *)malloc(sizeof(t_data))))
	{
		ft_putendl("doesn't malloced for a new file", 0);
		return (NULL);
	}
	node->name = str;
	node->len = ft_strlen(node->name);
	node->next = NULL;
	return (node);
}

void	push_back(t_data **head, t_data *node)
{
	t_data	*tmp;

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

size_t	ft_list_size(t_data *lst)
{
	size_t	i;
	t_data	*tmp;

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

void	ft_rev_list(t_data **head)
{
	t_data	*prev;
	t_data	*curr;
	t_data	*next;

	prev = NULL;
	next = NULL;
	curr = *head;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

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
