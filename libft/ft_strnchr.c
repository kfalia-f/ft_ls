#include <libft.h>

char	*ft_strnchr(const char *s, int c, size_t pos)
{
	if (s[pos] == (char)c)
		return ((char *)&s[pos]);
	return (NULL);
}
