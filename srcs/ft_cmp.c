#include <ft_ls.h>

int		ft_timecmp(long a, long b)
{
	if (a >= b)
		return (0);
	return (1);
}

void	ft_del_perms(char **perms, size_t list_size, t_data *head)
{
	ft_del(&perms, list_size);
	ft_free_perm(&head);
}
