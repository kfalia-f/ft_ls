#include <libft.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned const char	*chs;

	i = 0;
	chs = s;
	while (i < n)
	{
		if (chs[i] == (unsigned char)c)
			return ((void *)&s[i]);
		i++;
	}
	return (NULL);
}
