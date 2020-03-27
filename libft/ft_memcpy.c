#include <libft.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	const char	*chsrc;
	char		*chdst;

	i = 0;
	chsrc = src;
	chdst = dst;
	while (i < n)
	{
		chdst[i] = chsrc[i];
		i++;
	}
	return (dst);
}
