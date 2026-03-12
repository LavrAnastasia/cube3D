#include "parsing.h"

static t_parse_result make_parse_error_result(t_parse_error_code code, const char *info)
{
    return (t_parse_result) {
        .ok = false,
        .error = (t_parse_error) {
            .code = code,
            .info = info
        }
    };
}

static t_parse_result make_parse_succses_result()
{
    return (t_parse_result) {
        .ok = true
    };
}

static t_parse_result fill_texture_path(char *line, char **path, t_direction_key key)
{
    char *value;
    size_t len;

    if(*path != NULL)
        return make_parse_error_result(P_ERR_DUP, map_key(key));
    value = skip_spaces(line);
    if(!value || *value == '\0'|| *value == '\n')
        return make_parse_error_result(P_ERR_NO_PATH, map_key(key)); 
    *path = ft_strdup(value);
    if(!*path)
        return make_parse_error_result(P_ERR_MALLOC, NULL);
    len = ft_strlen(*path);
    if(len > 0 && (*path)[len - 1] == '\n') // added skip for space from end
        (*path)[len - 1] = '\0';
    return (make_parse_succses_result());
}
t_parse_result parse_color(char *raw, t_rgb *color, const char *key_name)
{
    char **rgb;
    
    rgb = ft_split(raw, ',');
    if(!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
        return make_parse_error_result(P_ERR_RGB, NULL);
    color->r = ft_atoi(rgb[0]);
    color->g = ft_atoi(rgb[1]);
    color->b = ft_atoi(rgb[2]);
    free_split(rgb);
    if(color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255 ||
        color->b < 0 || color->b > 255)
        return make_parse_error_result(P_ERR_RGB_RANGE, key_name);
    return make_parse_succses_result();
}

t_parse_result fill_texture_paths(char *line, t_game *game, t_parse_phase *phase)
{
    if(is_direction_key(line, NO))
        return(fill_texture_path(line + 2, &game->config.no_path, NO));
    if(is_direction_key(line, SO))
        return(fill_texture_path(line + 2, &game->config.so_path, SO));
    if(is_direction_key(line, WE))
        return(fill_texture_path(line + 2, &game->config.we_path, WE));
    if(is_direction_key(line, EA))
        return(fill_texture_path(line + 2, &game->config.ea_path, EA));
    *phase = P_COLORS;
    return  make_parse_succses_result();
}

t_parse_result fill_colors(char *trim, t_game *game,  t_parse_phase *phase)
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
    *phase = P_MAP;
    return make_parse_succses_result();
}

t_parse_result process_config_line(char *line, t_game *game, t_parse_phase *phase)
{
    char *trim;
    t_parse_result result;

    trim = skip_spaces(line);
    if (!trim || *trim == '\0' || *trim == '\n')
        return make_parse_succses_result();
    result = fill_texture_paths(trim, game, phase);
    if (!result.ok || (result.ok && *phase == P_TEXTURES))
        return (result);
    result = fill_colors(trim, game, phase);
    return (result);
}


