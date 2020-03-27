#include <libft.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;

	if (!(lst = (t_list *)malloc(sizeof(*lst))))
		return (NULL);
	if (content != NULL)
	{
		if (!(lst->content = ft_memalloc(content_size)))
		{
			free(lst);
			return (NULL);
		}
		lst->content = ft_memcpy(lst->content, content, content_size);
		lst->content_size = content_size;
	}
	else
	{
		lst->content = NULL;
		lst->content_size = 0;
	}
	lst->next = NULL;
	return (lst);
}
