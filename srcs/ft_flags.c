#include <ft_ls.h>

static void    ft_error(char c)
{
    // print usage / perror and exit.
}

static void    ft_check_flag(char *s, t_flags flags)
{
    size_t  i;
    size_t  j;
    char    *cmp;
    
    i = 1;
    j = 0;
    cmp = "Raflrt1";
    while (s[i] != '\0')
    {
        while (cmp[j] != '\0')
        {
            if (s[i] == cmp[j])
            {
                //do the job with bits
            }
            else
                ft_error(s[i]);
            j++;
        }
        i++;
    }
}

size_t        ft_flags(int ac, char **av, t_flags flags)
{
    size_t  i;
    size_t  num_of_flags;

    i = 1;
    num_of_flags = 0;
    while (i < ac)
    {
        if (av[i][0] == '-')
        {
            ft_check_flag(av[i], flags);
            num_of_flags++;
        }
        else
            break ;
        if (av[i][0] == '-' && av[i][1] == '-')
        {
            num_of_flags++;
            break ;
        }
        i++;
    }
    return (num_of_flags);
}
