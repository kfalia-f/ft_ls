#include <libft.h>

char	*ft_strjoinre(char *s1, const char *s2)
{
	char	*s;

	if ((s = ft_strjoin(s1, s2)) == NULL)
		return (NULL);
	free(s1);
	return (s);
}
