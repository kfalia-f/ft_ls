/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <kfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:44:08 by koparker          #+#    #+#             */
/*   Updated: 2019/04/28 13:34:05 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putendl(char const *s, int flag)
{
	if (flag == 2)
		ft_putchar_base('\n', 1);
	ft_putstr_base(s, 1);
	if (flag != 0)
		ft_putchar_base(':', 1);
	ft_putchar_base('\n', 1);
}
