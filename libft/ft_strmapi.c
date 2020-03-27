#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*res;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (!(res = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (i < ft_strlen(s))
	{
		res[i] = f(i, s[i]);
		i++;
	}
	return (res);
}
