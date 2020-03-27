#include <libft.h>

void	ft_lstpush_back(t_list **alst, t_list *new)
{
	t_list *tmp;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
