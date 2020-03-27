#include <libft.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	if (alst && del)
	{
		while ((*alst) != NULL)
		{
			tmp = *alst;
			del((*alst)->content, (*alst)->content_size);
			(*alst) = (*alst)->next;
			free(tmp);
		}
		free(*alst);
		*alst = NULL;
	}
}
