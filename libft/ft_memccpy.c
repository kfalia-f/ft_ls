#include <libft.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t		i;
	char		*chdst;
	const char	*chsrc;

	i = 0;
	chdst = (char *)dst;
	chsrc = (const char *)src;
	while (i < n)
	{
		chdst[i] = chsrc[i];
		if (chsrc[i] == (char)c)
			return (&dst[i + 1]);
		i++;
	}
	return (NULL);
}
