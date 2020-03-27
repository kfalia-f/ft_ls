#include <libft.h>

t_list	*ft_lstback(t_list *lst)
{
	if (lst)
		return (ft_lstat(lst, ft_listsize(lst) - 1));
	return (NULL);
}
