#include "parsing.h"

int parse_texture(char *raw, char **saved, const char *key_name)
{
    char *path;
    size_t len;

    path = skip_spaces(raw);
    if(!path || *path == '\0'|| *path == '\n')
        return(print_error_key(key_name, NO_PATH));
    *saved = ft_strdup(path);
    if(!*saved)
        return(print_error_msg(ERR_MALLOC));
    len = ft_strlen(*saved);
    if(len > 0 && (*saved)[len - 1] == '\n')
        (*saved)[len - 1] = '\0';
    return (0); 
}
int parse_color(char *raw, t_rgb *color, const char *key_name)
{
    char **rgb;
    
    rgb = ft_split(raw, ',');
    if(!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
        return(print_error_msg(ERR_RGB));
    color->r = ft_atoi(rgb[0]);
    color->g = ft_atoi(rgb[1]);
    color->b = ft_atoi(rgb[2]);
    free_split(rgb);
    if(color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255 ||
        color->b < 0 || color->b > 255)
        return(print_error_key(key_name, ERR_RGB_RANGE));
    return (0);
}

int handle_texture_key(char *trim, t_game *game)
{
    if(is_direction_config(trim, 'N', 'O'))
        return(parse_texture(trim + 2, &game->config.no_path, "NO"));
    if(is_direction_config(trim, 'S', 'O'))
        return(parse_texture(trim + 2, &game->config.so_path, "SO"));
    if(is_direction_config(trim, 'W', 'E'))
        return(parse_texture(trim + 2, &game->config.we_path, "WE"));
    if(is_direction_config(trim, 'E', 'A'))
        return(parse_texture(trim + 2, &game->config.ea_path, "EA"));
    return(1);
}

int handle_color_key(char *trim, t_game *game)
{
    char *path;

    if(is_config(trim, 'F'))
    {
        path = skip_spaces(trim + 1);
        return(parse_color(path, &game->config.floor, "F"));
    }
    if(is_config(trim, 'C'))
    {
        path = skip_spaces(trim + 1);
        return(parse_color(path, &game->config.ceiling, "C"));
    }
    return (1);
}

int parse_config_section(char *line, t_game *game)
{
    char *trim;
    int status;

    trim = skip_spaces(line);
    if(!trim || *trim == '\0' || *trim == '\n')
        return(0);
    status = handle_texture_key(trim, game);
    if(status != 1)
        return(status);
    status = handle_color_key(trim, game);
    if(status != 1)
        return(status);
    return(1);
}


