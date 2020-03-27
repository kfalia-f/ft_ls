static int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

static int	ft_islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int			ft_isalpha(int c)
{
	if (ft_isupper(c) == 1)
		return (1);
	else if (ft_islower(c) == 1)
		return (1);
	else
		return (0);
}
