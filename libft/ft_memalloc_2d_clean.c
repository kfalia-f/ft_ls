#include <libft.h>

char	**ft_memalloc_2d_clean(size_t str_num, size_t str_size)
{
	char	**s;
	size_t	k;

	if (str_num == 0 || str_size == 0)
		return (NULL);
	k = -1;
	if ((s = (char **)malloc(sizeof(char *) * (str_num + 1))) == NULL)
		return (NULL);
	while (++k < str_num)
		if ((s[k] = (char *)malloc(sizeof(char) * (str_size + 1))) == NULL)
			return (ft_del(&s, k));
	k = 0;
	while (k < str_num)
	{
		ft_bzero(s[k], '\0');
		k++;
	}
	s[str_num] = NULL;
	return (s);
}
