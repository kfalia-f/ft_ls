#include <ft_ls.h>

void	ft_lstcontent_to_char_arr(char **arr, t_data *data, size_t flag)
{
	t_data	*tmp;
	int		i;

	i = 0;
	tmp = data;
	while (tmp != NULL)
	{
		if (flag == 0)
			arr[i] = ft_strcpy(arr[i], tmp->name);
		else
			arr[i] = ft_strcpy(arr[i], tmp->perm);
		i++;
		tmp = tmp->next;
	}
}
