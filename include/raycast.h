#ifndef RAYCAST_H
# define RAYCAST_H

# include "types.h"

typedef enum e_ray_crossing
{
	R_CROSS_VERTICAL,
	R_CROSS_HORIZONTAL 
}	t_ray_crossing;

typedef struct s_ray_intersection
{
	t_point			point;
	t_ray_crossing	crossing;
	double			ray_length;
}   t_ray_intersection;

t_ray_intersection ray_dda(double angle, t_position player_pos, char **map, t_dimensions map_size);

#endif

