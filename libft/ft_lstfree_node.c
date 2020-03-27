#include <libft.h>

void	ft_lstfree_node(void *node, size_t size)
{
	free(node);
	size = 0;
}
