#include "parsing.h"
#include "get_next_line.h"
void init_config(t_config *config)
{
    config->no_path = NULL;
    config->so_path = NULL;
    config->we_path = NULL;
    config->ea_path = NULL;
    config->floor.r = -1;
    config->floor.g = -1;
    config->floor.b = -1;
    config->ceiling.r = -1;
    config->ceiling.g = -1;
    config->ceiling.b = -1;
}

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
    init_config(&game->config);
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