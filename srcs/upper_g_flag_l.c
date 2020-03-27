#include <ft_ls.h>

size_t	ft_sticky_file_l(char *perm, char *name)
{
	char	*tmp;

	tmp = NULL;
	if (*perm == '-')
	{
		if (ft_strrchr(perm, 't') || ft_strchr(perm, 'x'))
		{
			if (ft_strnchr(perm, 's', 3) || ft_strnchr(perm, 'S', 3))
				tmp = ft_strjoin(EXE_SETUID_COLOR, name);
			else if (ft_strnchr(perm, 's', 6) || ft_strnchr(perm, 'S', 6))
				tmp = ft_strjoin(EXE_SETGID_COLOR, name);
			else
				tmp = ft_strjoin(EXE_COLOR, name);
			ft_putstr(tmp);
			ft_strdel(&tmp);
			return (1);
		}
	}
	return (0);
}

size_t	ft_sticky_dir_l(char *perm, char *name)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strnchr(perm, 'w', 8) && *perm == 'd')
	{
		if (ft_strrchr(perm, 't') || ft_strrchr(perm, 'T'))
			tmp = ft_strjoin(STICKY_BIT_COLOR, name);
		else
			tmp = ft_strjoin(NO_STICKY_BIT_COLOR, name);
		ft_putstr(tmp);
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

void	ft_colorized_output_l(char *perm, char *name)
{
	char	*tmp;

	tmp = NULL;
	if (ft_sticky_file_l(perm, name) || ft_sticky_dir_l(perm, name))
		ft_putstr(RESET);
	else if (*perm == 'd')
		tmp = ft_strjoin(DIR_COLOR, name);
	else if (*perm == 'b')
		tmp = ft_strjoin(BLOCK_COLOR, name);
	else if (*perm == 'c')
		tmp = ft_strjoin(CHAR_COLOR, name);
	else if (*perm == 'l')
		tmp = ft_strjoin(SIMLNK_BASE_COLOR, name);
	else if (*perm == 's')
		tmp = ft_strjoin(SOCKET_COLOR, name);
	else if (ft_strchr(perm, 'x'))
		tmp = ft_strjoin(EXE_COLOR, name);
	else
		ft_putstr(name);
	if (tmp)
	{
		ft_putstr(tmp);
		ft_strdel(&tmp);
	}
	ft_putstr(RESET);
}
