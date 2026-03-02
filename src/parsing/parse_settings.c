#include "parsing.h"
#include "get_next_line.h"

int check_args(int argc, char **argv)
{
    char *dot;

    if(argc < 2)
        return(print_error_msg(NO_MAP));
    if(argc > 2)
        return(print_error_msg(MANY_ARG));
    dot = ft_strchr(argv[1], '.');
    if(!dot || ft_strncmp(dot, ".cub", 5)!= 0)
        return(print_error_msg(EXTENTION_MSG));
    return(0);    
}

int parse_settings(t_game *game, char **argv)
{
    int fd;
    char *line;
    (void)game;
    
    fd = open(argv[1], O_RDONLY);
    if(fd < 0)
        return(print_error_msg(OPEN_FILE));
    line = get_next_line(fd);
    while(line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return(0);
}