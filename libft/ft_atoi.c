static int	ft_is_wsp(char wsp)
{
	if (wsp == ' ' || wsp == '\t' || wsp == '\n' ||
			wsp == '\v' || wsp == '\f' || wsp == '\r')
		return (1);
	return (0);
}

static int	ft_overflow_check(int n, int sign)
{
	int	tmp;

	tmp = n;
	if (tmp * 10 / 10 != tmp && sign == 0)
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_is_wsp(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if (ft_overflow_check(res, sign) == 1)
			return (res);
		if (res < 0)
			return (sign == 1 ? -1 : 0);
	}
	if (sign == -1)
		return ((int)(-res));
	return ((int)res);
}
