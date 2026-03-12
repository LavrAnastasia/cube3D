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

int read_config_until_map(int fd, t_game *game, char **first_map_line)
{
    char *line;
    int status;

    *first_map_line = NULL;
    line = get_next_line(fd);
    if(!line)
        return(print_error_msg(ERR_MAP));
    while(line)
    {
        status = process_config_line(line, game);
        if(status == PARSE_ERR)
            return(free(line), 1);
        if(status == PARSE_MAP)
        {
            *first_map_line = line;
            return(0);
        }
        free(line);
        line = get_next_line(fd);
    }
    return(0);
}

int parse_settings(t_game *game, char **argv)
{
    int fd;
    char *first_map_line;

    fd = open(argv[1], O_RDONLY);
    if(fd < 0)
        return(print_error_msg(OPEN_FILE));
    if(read_config_until_map(fd, game, &first_map_line))
        return(close(fd), 1); //проверить что именно тут корректно возвращать 
    if(!first_map_line)
        return(close(fd), print_error_msg(ERR_MAP)); //и тут
    /*
        if(process_map_section(first_map_line, fd, game))
        return(close(fd), 1);
    */
   free(first_map_line);
   close(fd);
   return(0);
}