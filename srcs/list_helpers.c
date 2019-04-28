/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:40:08 by koparker          #+#    #+#             */
/*   Updated: 2019/04/28 13:44:34 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

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

void	ft_free_l_info(t_data **node)
{
	free((*node)->l_info->perm);
	(*node)->l_info->perm = NULL;
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

void	ft_free_perm(t_data **head)
{
	t_data	*tmp;

	tmp = NULL;
	if (*head == NULL)
		return ;
	tmp = *head;
	while (tmp)
	{
		free(tmp->perm);
		tmp->perm = NULL;
		tmp = tmp->next;
	}
}

void	ft_free_list(t_data **head, size_t flag_l)
{
	t_data	*tmp;

	tmp = NULL;
	if (*head == NULL)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->name);
		tmp->name = NULL;
		if (flag_l)
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
	while (tmp != NULL && *(tmp->name) == '.')
	{
		*head = tmp->next;
		ft_strdel(&(tmp->name));
		free(tmp);
		tmp = *head;
	}
	while (tmp)
	{
		while (tmp != NULL && *(tmp->name) != '.')
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			return ;
		prev->next = tmp->next;
		ft_strdel(&(tmp->name));
		free(tmp);
		tmp = prev->next;
	}
}
