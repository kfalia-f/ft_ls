#include <libft.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	if (s == NULL)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (!(substr = ft_strnew(len)))
		return (NULL);
	if (len <= s_len && start <= s_len)
	{
		while (i < len)
		{
			substr[i] = s[i + start];
			i++;
		}
	}
	return (substr);
}
