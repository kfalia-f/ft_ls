#include <libft.h>

void	ft_memdel(void **ap)
{
	char **tmp;

	if (ap == NULL)
		return ;
	tmp = (char **)ap;
	free(*tmp);
	*tmp = NULL;
}
