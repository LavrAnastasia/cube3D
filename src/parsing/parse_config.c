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


t_parse_result	parse_rgb_component(char **raw, int *out)
{
	char	*str;
	int		val;

	str = skip_spaces(*raw);
	if (str == NULL)
		return (make_parse_error_result(P_ERR_RGB, NULL));
	if (*str == '\0' || *str == '\n')
		return (make_parse_error_result(P_ERR_RGB, NULL));
	if (ft_isdigit((unsigned char)*str) == 0)
		return (make_parse_error_result(P_ERR_RGB, NULL));
	val = 0;
	while (ft_isdigit((unsigned char)*str))
	{
		val = (val * 10) + (*str - '0');
		if (val > 255)
			return (make_parse_error_result(P_ERR_RGB_RANGE, NULL));
        str++;
	}
	str = skip_spaces(str);
	*raw = str;
	*out = val;
	return (make_parse_success_result(P_COLOR));
}

t_parse_result parse_color(char *raw, t_rgb *color)
{
	char	*str;
    t_parse_result res;

	str = raw;
	res = parse_rgb_component(&str, &color->r);
	if (res.ok == false)
		return (res);
	if (*str != ',')
		return (make_parse_error_result(P_ERR_RGB, NULL));
	str++;

	res = parse_rgb_component(&str, &color->g);
	if (res.ok == false)
		return (res);
	if (*str != ',')
		return (make_parse_error_result(P_ERR_RGB, NULL));
	str++;

	res = parse_rgb_component(&str, &color->b);
	if (res.ok == false)
		return (res);

	str = skip_spaces(str);
	if (*str != '\0')
	{
		if (*str != '\n')
			return (make_parse_error_result(P_ERR_RGB, NULL));
	}
	return (make_parse_success_result(P_COLOR));
}

t_parse_result parse_texture_paths(char *line,t_configuration *configuration)
{
    if(is_direction_key(line, NO))
        return(parse_texture_path(line + 2, &configuration->samples.paths.north, NO));
    if(is_direction_key(line, SO))
        return(parse_texture_path(line + 2, &configuration->samples.paths.south, SO));
    if(is_direction_key(line, WE))
        return(parse_texture_path(line + 2, &configuration->samples.paths.west, WE));
    if(is_direction_key(line, EA))
        return(parse_texture_path(line + 2, &configuration->samples.paths.east, EA));
    return  make_parse_success_result(P_UNKNOWN);
}

t_parse_result parse_colors(char *trim, t_configuration *configuration, t_config_state *st)
{
    char *path;
    t_parse_result res;

    if(is_color_key(trim, C_FLOOR))
    {
        if(st->seen_floor)
            return(make_parse_error_result(P_ERR_DUP_FLOOR, NULL));
        path = skip_spaces(trim + 1);
        res = parse_color(path, &configuration->samples.floor);
        if(!res.ok)
            return(res);
        st->seen_floor = 1;
        return(res);
    }
    if(is_color_key(trim, C_CEILING))
    {
        if(st->seen_ceiling)
            return(make_parse_error_result(P_ERR_DUP_CEILING, NULL));
        path = skip_spaces(trim + 1);
        res = parse_color(path, &configuration->samples.ceiling);
        if(!res.ok)
            return(res);
        st->seen_ceiling = 1;
        return(res);
    }
    return make_parse_success_result(P_UNKNOWN);
}
static bool looks_like_map_line(const char *s)
{
    while (*s && ft_isspace((unsigned char)*s))
        s++;
    return (*s == TILE_WALL || *s == TILE_EMPTY
        || *s == TILE_PLAYER_NORTH || *s == TILE_PLAYER_SOUTH
        || *s == TILE_PLAYER_WEST || *s == TILE_PLAYER_EAST);
}

t_parse_result process_config_line(char *line, t_configuration *configuration, t_config_state *st)
{
    char *trim;
    t_parse_result result;


    trim = skip_spaces(line);
    if (!trim || *trim == '\0' || *trim == '\n')
        return make_parse_success_result(P_SPACES);
    result = parse_texture_paths(trim, configuration);
    if (!result.ok || (result.ok && result.parse_type == P_TEXTURE))
        return (result);
    result = parse_colors(trim, configuration, st);
    if (!result.ok)
        return (result);
    if (result.parse_type == P_UNKNOWN)
    {
        if (is_map_row(trim))
            result.parse_type = P_MAP;
        else if (looks_like_map_line(trim))
            return (make_parse_error_result(P_ERR_INVALID_SYMBOLS, NULL));
        else
            return (make_parse_error_result(P_ERR_INVALID_CONFIG_LINE, NULL));
    }
    return (result);
}


