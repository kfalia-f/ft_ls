#include <libft.h>

void	*ft_memalloc(size_t size)
{
	unsigned char *mem;

	if (!(mem = (unsigned char *)malloc(sizeof(*mem) * size)))
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}
