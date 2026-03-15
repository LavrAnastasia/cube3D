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

static t_parse_result make_parse_success_result(t_parse_type p_type)
{
    return (t_parse_result) {
        .ok = true,
        .parse_type = p_type
    };
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
    return make_parse_success_result(P_COLOR);
}

t_parse_result fill_texture_paths(char *line, t_game *game)
{
    if(is_direction_key(line, NO))
        return(fill_texture_path(line + 2, &game->config.paths.north, NO));
    if(is_direction_key(line, SO))
        return(fill_texture_path(line + 2, &game->config.paths.south, SO));
    if(is_direction_key(line, WE))
        return(fill_texture_path(line + 2, &game->config.paths.west, WE));
    if(is_direction_key(line, EA))
        return(fill_texture_path(line + 2, &game->config.paths.east, EA));
    return  make_parse_success_result(P_UNKNOWN);
}

t_parse_result fill_colors(char *trim, t_game *game)
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
    return make_parse_success_result(P_UNKNOWN);
}

t_parse_result process_config_line(char *line, t_game *game)
{
    char *trim;
    t_parse_result result;

    trim = skip_spaces(line);
    if (!trim || *trim == '\0' || *trim == '\n')
        return make_parse_success_result(P_SPACES);
    result = fill_texture_paths(trim, game);
    if (!result.ok || (result.ok && result.parse_type == P_TEXTURE))
        return (result);
    result = fill_colors(trim, game);
    if (!result.ok)
        return (result);
    if (result.parse_type == P_UNKNOWN)
        result.parse_type = P_MAP;
    return (result);
}


