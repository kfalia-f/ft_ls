#include <libft.h>

t_list	*ft_lstat(t_list *lst, size_t pos)
{
	size_t	i;
	t_list	*at;

	i = 0;
	at = lst;
	if (lst)
	{
		while (at->next && i != pos)
		{
			at = at->next;
			i++;
		}
	}
	return (at);
}
