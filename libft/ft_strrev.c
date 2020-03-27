#include <libft.h>

char	*ft_strrev(char *s)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = ft_strlen(s);
	j = 0;
	res = (char *)malloc(sizeof(*res) * (i + 1));
	while (s[j])
	{
		res[j++] = s[--i];
	}
	res[j] = '\0';
	return (res);
}
