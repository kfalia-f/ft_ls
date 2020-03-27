#include <libft.h>

char	*ft_strmap(char const *s, char (*f)(char))
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
		res[i] = f(s[i]);
		i++;
	}
	return (res);
}
