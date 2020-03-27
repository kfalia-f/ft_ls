#include <libft.h>

void	ft_striter(char *s, void (*f)(char *))
{
	size_t i;
	size_t len;

	if (s != NULL && f != NULL)
	{
		i = 0;
		len = ft_strlen(s);
		while (i < len)
		{
			f(&s[i]);
			i++;
		}
	}
}
