#include <libft.h>

void	*ft_memcpy_backwards(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*chdst;
	const char	*chsrc;

	chdst = dst;
	chsrc = src;
	if (n == 0)
		return (dst);
	i = n - 1;
	while (i > 0)
	{
		chdst[i] = chsrc[i];
		i--;
	}
	chdst[i] = chsrc[i];
	return (dst);
}
