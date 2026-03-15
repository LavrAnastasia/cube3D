#include "parsing.h"
#include "get_next_line.h"

static t_parse_result make_parse_error_result(t_parse_error_code code)
{
    return (t_parse_result) {
        .ok = false,
        .error = (t_parse_error) {
            .code = code,
            .info = NULL
        }
    };
}

t_parse_result check_args(int argc, char **argv)
{
    char *dot;
    t_parse_result result;

    result.ok = true;
    if(argc < 2)
        return(
            make_parse_error_result(P_ERR_NO_MAP));
    if(argc > 2)
        return(make_parse_error_result(P_ERR_ARG));
    dot = ft_strrchr(argv[1], '.');
    if(!dot || ft_strncmp(dot, ".cub", 5)!= 0)
        return(make_parse_error_result(P_ERR_EXTENSION));
    return (result);    
}

t_parse_result read_config_until_map(int fd, t_game *game, char **first_map_line)
{
    char *line;
    t_parse_result  result;
    t_parse_phase   phase;

    *first_map_line = NULL;
    line = get_next_line(fd);
    if(!line)
        return make_parse_error_result(P_ERR_NO_MAP);
    phase = P_TEXTURES;
    while(line)
    {
        result = process_config_line(line, game, &phase); // SHOULD KEEP GOOING
        if(!result.ok)
        {
            free(line);
            return (result);
        }
        if (phase != P_TEXTURES && phase != P_COLORS)
        {
            *first_map_line = line;
            return(result); // TODO: check that it is safe
        }
        free(line);
        line = get_next_line(fd);
    }
    return (result); // TODO: check that it is safe
}

t_parse_result parse_settings(t_game *game, char **argv)
{
    int fd;
    char *first_map_line;
    t_parse_result result;

    fd = open(argv[1], O_RDONLY);
    if(fd < 0)
        return (make_parse_error_result(P_ERR_OPEN_FILE));
    result = read_config_until_map(fd, game, &first_map_line);
    if (!result.ok)
    {
        close(fd);
        return result;
    }
    if(!first_map_line)
    {
        close(fd);
        return make_parse_error_result(P_ERR_NO_MAP);
    }
        
    /*
        if(process_map_section(first_map_line, fd, game))
        return(close(fd), 1);
    */
   free(first_map_line);
   close(fd);
   result.ok = true;
   return(result);
}