#include "parsing.h"
#include "get_next_line.h"

int check_args(int argc, char **argv)
{
    char *dot;

    if(argc < 2)
        return(print_error_msg(NO_MAP));
    if(argc > 2)
        return(print_error_msg(MANY_ARG));
    dot = ft_strrchr(argv[1], '.');
    if(!dot || ft_strncmp(dot, ".cub", 5)!= 0)
        return(print_error_msg(EXTENTION_MSG));
    return(0);    
}

int parse_settings(t_game *game, char **argv)
{
    int fd;
    char *line;
    int status;
    char *first_map_line;
    
    fd = open(argv[1], O_RDONLY);
    if(fd < 0)
        return(print_error_msg(OPEN_FILE));
    init_config(&game->config);
    first_map_line = NULL;
    line = get_next_line(fd);
    if(!line)
        close(fd);
        return(1);
    while(line)
    {
        status = parse_config_section(line, game);
        if(status == -1)
            return(parse_clean(fd, line));
        if(status == 1)
        {
            first_map_line = line;
            // parse_map_section(line, fd, game)
            break;
        }
        free(line);
        line = get_next_line(fd);
    }
    if(!first_map_line)
        return(close(fd), print_error_msg(ERR_MAP));
    close(fd);
    return(0);
}
