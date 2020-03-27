#include <libft.h>

void	ft_putstr_base(char const *s, int out)
{
	write(out, s, ft_strlen(s));
}
