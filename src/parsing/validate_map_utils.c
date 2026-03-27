#include "map_utils.h"
#include "parsing_internal.h"

int	is_valid_map_rows(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		if (!is_map_row(map[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_walkable(char c)
{
	return (c == TILE_EMPTY || is_player_pos(c));
}

static int	is_out_of_map(char **map, int rows, int x, int y)
{
	int	len;

	if (y < 0 || y >= rows || x < 0)
		return (1);
	len = row_len(map[y]);
	if (x >= len)
		return (1);
	return (0);
}
int	flood_fill(char **map, int rows, int x, int y)
{
	char c;

	if (is_out_of_map(map, rows, x, y))
		return (1);
	c = map[y][x];
	if (c == SKIP_SIGN)
		return (1);
	if (c == TILE_WALL || c == VISITED_SIGN)
		return (0);
	if (!is_walkable(c))
		return (0);
	map[y][x] = VISITED_SIGN;
	if (flood_fill(map, rows, x - 1, y))
		return (1);
	if (flood_fill(map, rows, x + 1, y))
		return (1);
	if (flood_fill(map, rows, x, y - 1))
		return (1);
	if (flood_fill(map, rows, x, y + 1))
		return (1);
	return (0);
}