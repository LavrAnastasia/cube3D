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

static char *map_color_key(t_color_key key)
{
    if (key == C_FLOOR)
        return FLOOR_KEY;
    return CEILING_KEY;  
}
t_parse_result parse_color(char *raw, t_rgb *color, t_color_key key)
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
        return make_parse_error_result(P_ERR_RGB_RANGE, map_color_key(key));
    return make_parse_success_result(P_COLOR);
}

t_parse_result fill_texture_paths(char *line,t_configuration *configuration)
{
    if(is_direction_key(line, NO))
        return(fill_texture_path(line + 2, &configuration->samples.paths.north, NO));
    if(is_direction_key(line, SO))
        return(fill_texture_path(line + 2, &configuration->samples.paths.south, SO));
    if(is_direction_key(line, WE))
        return(fill_texture_path(line + 2, &configuration->samples.paths.west, WE));
    if(is_direction_key(line, EA))
        return(fill_texture_path(line + 2, &configuration->samples.paths.east, EA));
    return  make_parse_success_result(P_UNKNOWN);
}

t_parse_result fill_colors(char *trim, t_configuration *configuration)
{
    char *path;

    if(is_config(trim, C_FLOOR))
    {
        path = skip_spaces(trim + 1);
        return(parse_color(path, &configuration->samples.floor, C_FLOOR));
    }
    if(is_config(trim, C_CEILING))
    {
        path = skip_spaces(trim + 1);
        return(parse_color(path, &configuration->samples.ceiling, C_CEILING));
    }
    return make_parse_success_result(P_UNKNOWN);
}

t_parse_result process_config_line(char *line, t_configuration *configuration)
{
    char *trim;
    t_parse_result result;

    trim = skip_spaces(line);
    if (!trim || *trim == '\0' || *trim == '\n')
        return make_parse_success_result(P_SPACES);
    result = fill_texture_paths(trim, configuration);
    if (!result.ok || (result.ok && result.parse_type == P_TEXTURE))
        return (result);
    result = fill_colors(trim, configuration);
    if (!result.ok)
        return (result);
    if (result.parse_type == P_UNKNOWN)
        result.parse_type = P_MAP;
    return (result);
}


