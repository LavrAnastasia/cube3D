#include "parsing.h"

char *skip_spaces(char *s)
{
    if(!s)
        return (NULL);
    while (ft_isspace(*s))
        s++;
    return(s);
}
int print_error_msg(char *msg)
{
    ft_putendl_fd("Error", STDERR_FILENO);
    ft_putendl_fd(msg, STDERR_FILENO);
    return(1);
}

int	print_error_key(const char *key, const char *msg)
{
    ft_putendl_fd("Error", STDERR_FILENO);
    if(key && *key)
    {
        ft_putstr_fd((char *)key, STDERR_FILENO);
        ft_putstr_fd(":", STDERR_FILENO);
    }
    ft_putendl_fd(msg, STDERR_FILENO);
    return(1);
}

int parse_clean(int fd, char *line)
{
    free(line);
    close(fd);
    return(1);
}

void free_split(char **arr)
{
    int i;

    if(!arr)
        return ;
    i = 0;
    while(arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}