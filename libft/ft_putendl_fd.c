#include <libft.h>

void	ft_putendl_fd(char const *s, int fd)
{
	ft_putstr_base(s, fd);
	ft_putchar_base('\n', fd);
}
