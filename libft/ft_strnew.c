#include <libft.h>

char	*ft_strnew(size_t size)
{
	if (size * 10 / 10 != size)
		return (NULL);
	return ((char *)ft_memalloc(size + 1));
}
