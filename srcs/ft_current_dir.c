/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_current_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:52:55 by koparker          #+#    #+#             */
/*   Updated: 2019/04/05 21:59:54 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_data	*ft_current_dir(char *s)
{
	DIR		*dirp;
	t_data	*head;

	head = NULL;
	dirp = opendir(s);
	head = ft_readdir(dirp);
	closedir(dirp);
	return (head);
}
