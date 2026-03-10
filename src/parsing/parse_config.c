#include "parsing.h"

static bool fill_texture_path(char *line, char **path, t_direction_key key)
{
    char *value;
    size_t len;

    value = skip_spaces(line);
    if(!value || *value == '\0'|| *value == '\n')
    {
        print_error_key(map_key(key), NO_PATH);
        return (false);
    }
        
    *path = ft_strdup(value);
    if(!*path)
    {
        print_error_msg(ERR_MALLOC);
        return (false);
    }
        
    len = ft_strlen(*path);
    if(len > 0 && (*path)[len - 1] == '\n') //TODO added skip for space from end
        (*path)[len - 1] = '\0';
    return (true); 
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

bool fill_texture_paths(char *line, t_game *game)
{
    if(is_direction_key(line, NO))
        return(fill_texture_path(line + 2, &game->config.no_path, NO));
    if(is_direction_key(line, SO))
        return(fill_texture_path(line + 2, &game->config.so_path, SO));
    if(is_direction_key(line, WE))
        return(fill_texture_path(line + 2, &game->config.we_path, WE));
    if(is_direction_key(line, EA))
        return(fill_texture_path(line + 2, &game->config.ea_path, EA));
    return(false);
}

int fill_colors(char *trim, t_game *game)
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
    if (fill_texture_paths(trim, game)) // TODO: ya uhogu is lupu tak kak smogla zapolnit stroku
        return 0;
    status = fill_colors(trim, game);
    if(status != 1)
        return(status);
    return(1);
}


