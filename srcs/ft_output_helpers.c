#include <ft_ls.h>

size_t	ft_max_namlen(t_data *data)
{
	t_data	*tmp;
	size_t	max;

	if (data == NULL)
		return (0);
	tmp = data;
	max = tmp->len;
	while (tmp)
	{
		if (max < tmp->len)
			max = tmp->len;
		tmp = tmp->next;
	}
	return (max);
}

void	ft_sps(char *str, size_t len)
{
	ft_putstr(str);
	ft_output_spaces(' ', len);
}

void	ft_output_spaces(char c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		ft_putchar(c);
		i++;
	}
}

void	ft_skip_dots(t_data **head, t_flags fl)
{
	int i;

	i = 0;
	while ((*(*head)->name) == '.')
	{
		if ((fl.bits.a == 1 || fl.bits.f == 1) && i == 2)
			break ;
		i++;
		*head = (*head)->next;
	}
}

void	ft_process_dirs_helper(size_t *flag)
{
	if (*flag == 1)
		*flag = 2;
	ft_putchar('\n');
}
