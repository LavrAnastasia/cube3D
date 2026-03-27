#include "parsing_internal.h"

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
	return (make_parse_success_result());
}

static t_parse_result	find_rgb_component(char **str, int *dst, int comma)
{
	t_parse_result	res;

	res = parse_rgb_component(str, dst);
	if (!res.ok)
		return (res);
	if (comma)
	{
		if (**str != ',')
			return (make_parse_error_result(P_ERR_RGB, NULL));
		(*str)++;
	}
	return (make_parse_success_result());
}

t_parse_result	parse_color_line(char *raw, t_rgb *color)
{
	char			*str;
	t_parse_result	res;

	str = raw;
	res = find_rgb_component(&str, &color->r, true);
	if (res.ok == false)
		return (res);
	res = find_rgb_component(&str, &color->g, true);
	if (res.ok == false)
		return (res);
	res = find_rgb_component(&str, &color->b, false);
	if (res.ok == false)
		return (res);
	str = skip_spaces(str);
	if (*str != '\0' && *str != '\n')
		return (make_parse_error_result(P_ERR_RGB, NULL));
	return (make_parse_success_result());
}

t_parse_result	parse_texture(char *line, t_configuration *configuration)
{
	if (is_direction_key(line, NO))
		return (parse_texture_line(line + 2,
				&configuration->samples.paths.north, NO));
	if (is_direction_key(line, SO))
		return (parse_texture_line(line + 2,
				&configuration->samples.paths.south, SO));
	if (is_direction_key(line, WE))
		return (parse_texture_line(line + 2, &configuration->samples.paths.west,
				WE));
	if (is_direction_key(line, EA))
		return (parse_texture_line(line + 2, &configuration->samples.paths.east,
				EA));
	return (make_parse_success_result());
}

static t_parse_result	parse_single_color(char *trim, int *seen, t_rgb *dst, t_parse_error_code dup_err)
{
	t_parse_result	res;

	if (*seen)
		return (make_parse_error_result(dup_err, NULL));
	res = parse_color_line(skip_spaces(trim + 1), dst);
	if (!res.ok)
		return (res);
	*seen = 1;
	return (res);
}

t_parse_result	parse_color(char *trim, t_configuration *configuration, t_config_state *st)
{
	if (is_color_key(trim, C_FLOOR))
		return (parse_single_color(
			trim, &st->seen_floor, &configuration->samples.floor, P_ERR_DUP_FLOOR));
	if (is_color_key(trim, C_CEILING))
		return (parse_single_color(
			trim, &st->seen_ceiling, &configuration->samples.ceiling, P_ERR_DUP_CEILING));
	return (make_parse_success_result());
}

static bool	looks_like_map_line(const char *s)
{
	while (*s && ft_isspace((unsigned char)*s))
		s++;
	return (*s == TILE_WALL || *s == TILE_EMPTY || *s == TILE_PLAYER_NORTH
		|| *s == TILE_PLAYER_SOUTH || *s == TILE_PLAYER_WEST
		|| *s == TILE_PLAYER_EAST);
}

int	is_texture_line(char *trim)
{
	return (is_direction_key(trim, NO) || is_direction_key(trim, SO)
		|| is_direction_key(trim, WE) || is_direction_key(trim, EA));
}

int	is_color_line(char *trim)
{
	return (is_color_key(trim, C_FLOOR) || is_color_key(trim, C_CEILING));
}

t_parse_result	process_config_line(char *line, t_configuration *configuration,
		t_config_state *state, t_parse_type *type)
{
	char	*trim;

	*type = P_NONE;
	trim = skip_spaces(line);
	if (!trim || *trim == '\0' || *trim == '\n')
		return (make_parse_success_result());
	if (is_texture_line(trim))
	{
		*type = P_TEXTURE;
		return (parse_texture(trim, configuration));
	}
	if (is_color_line(trim))
	{
		*type = P_COLOR;
		return (parse_color(trim, configuration, state));
	}
	if (is_map_row(trim))
	{
		*type = P_MAP;
		return (make_parse_success_result());
	}
	if (looks_like_map_line(trim))
		return (make_parse_error_result(P_ERR_INVALID_SYMBOLS, NULL));
	return (make_parse_error_result(P_ERR_INVALID_CONFIG_LINE, NULL));
}
