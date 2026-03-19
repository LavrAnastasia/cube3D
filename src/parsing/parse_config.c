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

static int	parse_rgb_component(char **raw, int *out)
{
	char	*str;
	int		val;

	str = skip_spaces(*raw);
	if (!ft_isdigit((unsigned char)*str))
		return (0);
	val = 0;
	while (ft_isdigit((unsigned char)*str))
	{
		val = (val * 10) + (*str - '0');
		if (val > 255)
			return (0);
        str++;
	}
	str = skip_spaces(str);
	*raw = str;
	*out = val;
	return (1);
}

t_parse_result parse_color(char *raw, t_rgb *color, t_color_key key)
{
	char	*str;

	str = raw;
	if (!parse_rgb_component(&str, &color->r) || *str != ',')
		return (make_parse_error_result(P_ERR_RGB, map_color_key(key)));
    str++;
	if (!parse_rgb_component(&str, &color->g) || *str != ',')
		return (make_parse_error_result(P_ERR_RGB, map_color_key(key)));
    str++;
	if (!parse_rgb_component(&str, &color->b))
		return (make_parse_error_result(P_ERR_RGB, map_color_key(key)));
    str = skip_spaces(str);
	if (*str != '\0' && *str != '\n')
		return (make_parse_error_result(P_ERR_RGB, map_color_key(key)));
	return (make_parse_success_result(P_COLOR));
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
    t_parse_result res;

    if(is_config(trim, C_FLOOR))
    {
        if(configuration->samples.seen_floor)
            return(make_parse_error_result(P_ERR_DUP_FLOOR, FLOOR_KEY));
        path = skip_spaces(trim + 1);
        res = parse_color(path, &configuration->samples.floor, C_FLOOR);
        if(!res.ok)
            return(res);
        configuration->samples.seen_floor = 1;
        return(res);
    }
    if(is_config(trim, C_CEILING))
    {
        if(configuration->samples.seen_ceiling)
            return(make_parse_error_result(P_ERR_DUP_CEILING, CEILING_KEY));
        path = skip_spaces(trim + 1);
        res = parse_color(path, &configuration->samples.ceiling, C_CEILING);
        if(!res.ok)
            return(res);
        configuration->samples.seen_ceiling = 1;
        return(res);
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
    {
        if(is_map_line(trim))
        result.parse_type = P_MAP;
        else
            return(make_parse_error_result(P_ERR_INVALID_CHAR, NULL));
    }
    return (result);
}


