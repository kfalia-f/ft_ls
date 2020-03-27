#include <libft.h>

void	ft_putnbr_base(int n, int out)
{
	long tmp;

	tmp = n;
	if (tmp < 0)
	{
		tmp *= -1;
		ft_putchar_base('-', out);
	}
	if (tmp >= 10)
		ft_putnbr_base(tmp / 10, out);
	ft_putchar_base(tmp % 10 + '0', out);
}
