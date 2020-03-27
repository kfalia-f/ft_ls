#include <libft.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*chsrc;
	char		*chdst;

	chsrc = src;
	chdst = dst;
	if (chdst > chsrc)
		return ((void *)ft_memcpy_backwards(chdst, chsrc, len));
	if (chdst < chsrc)
		return ((void *)ft_memcpy(chdst, chsrc, len));
	else
		return (dst);
}
