#include "parsing.h"

int print_error_msg(char *msg)
{
    ft_putendl_fd("Error", STDERR_FILENO);
    ft_putendl_fd(msg, STDERR_FILENO);
    return(1);
}