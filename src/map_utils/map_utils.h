#ifndef MAP_UTILS_H
# define MAP_UTILS_H

#include "types.h"

int	is_in_bounds(t_point point, t_dimensions size);
int	is_wall(t_point point, char **map);

#endif