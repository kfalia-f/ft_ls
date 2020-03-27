#include <libft.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	void	*res;

	i = 0;
	res = b;
	while (i < len)
	{
		*(unsigned char *)b = (unsigned char)c;
		i++;
		b++;
	}
	return (res);
}
