#include "parsing_internal.h"

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
