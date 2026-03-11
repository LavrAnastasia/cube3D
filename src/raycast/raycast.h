#ifndef RAYCAST_H
# define RAYCAST_H

# include "raycast_types.h"

t_ray_intersection ray_dda(double angle, t_position player_pos, char **map, t_dimensions map_size);

#endif

