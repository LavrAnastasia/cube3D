#ifndef RAYCAST_INTERNAL_H
# define RAYCAST_INTERNAL_H

# include <math.h>
# include <float.h>

#include "raycast_types.h"

typedef struct s_axis_distance {
	double x;
	double y;
} t_axis_distance;

typedef struct s_cell_step {
	int x;
	int y;
} t_cell_step;

typedef struct s_dda_state {
	t_axis_distance one_step_distance;
	t_axis_distance distance_to_next_crossing;
	t_point 		current_cell;
	t_cell_step		step;
} t_dda_state;

typedef struct s_ray_info {
	t_vector direction;
	t_axis_direction axis_direction;
} t_ray_info;

t_ray_info			make_ray_info(double angle);
t_dda_state			make_initial_dda_state(t_ray_info ray, t_position start_position);
t_ray_intersection	make_invalid_intersection();
t_ray_intersection	make_ray_intersection(
	t_dda_state state,
	t_ray_info	ray,
	t_ray_crossing current_crossing,
	t_dimensions map_size
);

#endif