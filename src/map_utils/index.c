#include "map.h"
#include "types.h"

int	is_in_bounds(t_point point, t_dimensions size)
{
	return (
		point.x >= 0 && point.x < size.width
		&& point.y >= 0 && point.y < size.height
	);
}

int	is_wall(t_point point, char **map)
{
    return (map[point.y][point.x] == TILE_WALL);
}
