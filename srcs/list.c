/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:27:53 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/25 13:04:23 by koparker         ###   ########.fr       */
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
	node->name = ft_strdup(dp->d_name);
	node->len = ft_strlen(dp->d_name);
	node->next = NULL;
	return (node);
}

void	new_l_node(t_data **av, char *path, t_flags fl)
{
	char	*pt;

	if (!fl.bits.d)
		pt = (*av)->name;
	else
		pt = path;
	if (!((*av)->l_info = (t_lflag *)malloc(sizeof(t_lflag))))
	{
		ft_putendl("doesn't malloced for a new l node", 0);
		return ;
	}
	(*av)->l_info->file_name = ft_strdup(pt);
	(*av)->l_info->link = NULL;
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
	ft_bzero(node->name, name_size);
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

void 	ft_free_l_info(t_data **node)
{
	free((*node)->l_info->permissions);
	(*node)->l_info->permissions = NULL;
	free((*node)->l_info->owner);
	(*node)->l_info->owner = NULL;
	free((*node)->l_info->group);
	(*node)->l_info->group = NULL;
	free((*node)->l_info->date);
	(*node)->l_info->date = NULL;
	free((*node)->l_info->file_name);
	(*node)->l_info->file_name = NULL;
	if ((*node)->l_info->link)
	{
		free((*node)->l_info->link);
		(*node)->l_info->link = NULL;
	}
	free((*node)->l_info);
	(*node)->l_info = NULL;
}

void	ft_free_list(t_data **head, int flag)
{
	t_data	*tmp;

	if (*head == NULL)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->name);
		tmp->name = NULL;
		if (flag)
			ft_free_l_info(&tmp);
		free(tmp);
		tmp = NULL;
	}
}

void	ft_remove_dots(t_data **head)
{
	t_data	*tmp;
	t_data	*prev;

	tmp = *head;
	while (tmp != NULL && (!ft_strcmp(tmp->name, ".") || !ft_strcmp(tmp->name, "..")))
	{
		*head = tmp->next;
		free(tmp);
		tmp = *head;
	}
	while (tmp)
	{
		while (tmp != NULL && (!ft_strcmp(tmp->name, ".") || !ft_strcmp(tmp->name, "..")))
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			return ;
		prev->next = tmp->next;
		free(tmp);
		tmp = prev->next;
	}
}
