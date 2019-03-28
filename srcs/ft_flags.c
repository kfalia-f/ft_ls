/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:03:17 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/03/28 16:58:54 by kfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void    ft_wrong_flag(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putendl("\nusage: ./ft_ls [-Rafltr1] [file ...]", 0);
	exit(EXIT_FAILURE);
}

static void    ft_check_flag(char *str, t_flags flags)
{
    size_t  i;
	size_t	bits_to_shift;
    char    *cmp;
	char	*s;
    
    i = 1;
    cmp = "Raflrt1";
    while (str[i])
    {
		if ((s = ft_strchr(cmp, str[i])) != NULL)
			bits_to_shift = s - cmp;
		else
			ft_wrong_flag(str[i]);
		flags.value |= (1 << bits_to_shift);
		i++;
    }
}

size_t        ft_flags(int ac, char **av, t_flags flags)
{
    int  i;
    size_t  num_of_flags;

    i = 1;
    num_of_flags = 0;
    while (i < ac)
    {
        if (av[i][0] == '-' && av[i][1] == '-')
        {
            num_of_flags++;
			if (av[i][2] != '\0')
				ft_wrong_flag('-');
            break ;
        }
        if (av[i][0] == '-')
        {
            ft_check_flag(av[i], flags);
            num_of_flags++;
        }
        else
            break ;
        i++;
    }
    return (num_of_flags);
}
