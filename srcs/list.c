/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:27:53 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/12 16:18:31 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_data	*new_node(struct dirent *dp)
{
	t_data	*node;
	size_t	name_size;

	if (!(node = (t_data *)malloc(sizeof(t_data))))
	{
		ft_putendl("doesn't malloced for a new node", 0);
		return (NULL);
	}
	name_size = ft_strlen(dp->d_name);
	if (!(node->name = (char *)malloc(sizeof(char) * (name_size + 1))))
	{
		free(node);
		return (NULL);
	}
	ft_strcpy(node->name, dp->d_name);
	node->len = name_size;
	node->next = NULL;
	return (node);
}

t_lflag	*new_l_node(struct dirent *dp)
{
	t_lflag		*node;
	size_t		name_size;

	if (!(node = (t_lflag *)malloc(sizeof(t_lflag))))
	{
		ft_putendl("doesn't malloced for a new node", 0);
		return (NULL);
	}
	name_size = ft_strlen(dp->d_name);
	if (!(node->file_name = (char *)malloc(sizeof(char) * (name_size + 1))))
	{
		free(node);
		return (NULL);
	}
	node->date = (char *)malloc(sizeof(char) * 13);
	ft_strcpy(node->file_name, dp->d_name);
	node->link = NULL;
	node->next = NULL;
	return (node);
}

t_data	*new_file(char *str)
{
	t_data	*node;
	size_t	name_size;

	if (!(node = (t_data *)malloc(sizeof(t_data))))
	{
		ft_putendl("doesn't malloced for a new file", 0);
		return (NULL);
	}
	name_size = ft_strlen(str);
	if (!(node->name = (char *)malloc(sizeof(char) * (name_size + 1))))
	{
		free(node);
		return (NULL);
	}
	ft_strcat(node->name, str);
	node->len = name_size;
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

void	l_push_back(t_lflag **head, t_lflag *node)
{
	t_lflag	*tmp;

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
		free(tmp->name);
		free(tmp);
		tmp = NULL;
	}
}
