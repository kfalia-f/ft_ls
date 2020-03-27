#include <libft.h>

void	*ft_del(char ***a, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free((*a)[i]);
		(*a)[i] = NULL;
		i++;
	}
	free(*a);
	*a = NULL;
	return (NULL);
}
