/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:27:45 by kfalia-f          #+#    #+#             */
/*   Updated: 2019/04/10 18:07:25 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_swap(char **a, char **b)
{
	char *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_swap_mtime(long *a, long *b)
{
	long tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_ascii_sort_params(char **av)
{
	int	i;
	int j;

	i = 0;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[j + 1] != NULL)
		{
			if (ft_strcmp(av[j], av[j + 1]) > 0)
				ft_swap(&av[j], &av[j + 1]);
			j++;
		}
		i++;
	}
}

long	*ft_mtime(char **av)
{
	struct stat	buff;
	long		*mtime;
	size_t		size;
	size_t		i;

	size = ft_2d_strlen(av);
	mtime = (long *)malloc(sizeof(long) * size);
	i = 0;
	while (av[i])
	{
		stat(av[i], &buff);
		mtime[i] = buff.st_mtime;
		i++;
	}
	return (mtime);
}

void	ft_lmt_sort_params(char **av, long *mtime)
{
	int			i;
	int			j;

	i = 0;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[j + 1] != NULL)
		{
			if (ft_mtimecmp(mtime[j], mtime[j + 1]) == 1)
			{
				ft_swap(&av[j], &av[j + 1]);
				ft_swap_mtime(&mtime[j], &mtime[j + 1]);
			}
			j++;
		}
		i++;
	}
	free(mtime);
	mtime = NULL;
}

// under construction
void	ft_sort_params(char **av, int num_of_flags, t_flags fl)
{
	if (fl.bits.f == 1)
		return ;
	if (num_of_flags == 0 || fl.bits.a == 1 || fl.bits.l == 1 || fl.bits.one == 1)
		ft_ascii_sort_params(av);
	if (fl.bits.t == 1)
	{
		ft_lmt_sort_params(av, ft_mtime(av));
	//	ft_ascii_sort_params(av);
	}
}
