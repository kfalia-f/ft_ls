#include <libft.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t i;
	size_t len;

	if (s != NULL && f != NULL)
	{
		i = 0;
		len = ft_strlen(s);
		while (i < len)
		{
			f(i, &(s[i]));
			i++;
		}
	}
}
