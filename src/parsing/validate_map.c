#include "map_utils.h"
#include "parsing_internal.h"

t_parse_result	validate_map(char **map, t_configuration *configuration,
	int height)
{
if (!is_valid_map_rows(map))
	return (make_parse_error_result(P_ERR_INVALID_SYMBOLS, NULL));
if (!validate_player_pos(map, configuration))
	return (make_parse_error_result(P_ERR_PLAYER_COUNT, NULL));
return (is_map_closed(map, height, configuration->player_pos));
}
bool	validate_player_pos(char **map, t_configuration *config)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			if (is_player_pos(map[y][x]))
			{
				if (count > 0)
					return (false);
				config->player_pos.x = x + 0.5;
				config->player_pos.y = y + 0.5;
				config->player_start = map[y][x];
				count++;
			}
			x++;
		}
		y++;
	}
	return (count == 1);
}

char	**copy_map(char **map, int rows)
{
	char	**copy;
	int		i;

	copy = ft_calloc(rows + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (free_str_array(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
t_parse_result	is_map_closed(char **map, int rows, t_position position)
{
	char	**copy;
	int		leak;

	copy = copy_map(map, rows);
	if (!copy)
		return (make_parse_error_result(P_ERR_MALLOC, NULL));
	leak = flood_fill(copy, rows, position.x, position.y);
	free_str_array(copy);
	if (leak != 0)
		return (make_parse_error_result(P_ERR_MAP_NOT_CLOSED, NULL));
	return (make_parse_success_result());
}
