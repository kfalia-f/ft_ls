#include <libft.h>

size_t	ft_2d_strlen(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
