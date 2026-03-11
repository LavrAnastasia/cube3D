#include "raycast_internal.h"
#include "map_utils.h"

t_ray_intersection make_invalid_intersection()
{
	// TODO: make warning
	return (t_ray_intersection){
		.point = (t_point){ .x = 0, .y = 0 },
		.crossing = R_CROSS_VERTICAL,
		.ray_length = DBL_MAX,
		.ray_direction = (t_vector) {.x = 0, .y = 0},
		.axis_direction = (t_axis_direction) { .x = X_NONE, .y = Y_NONE }
	};
}

t_ray_intersection make_ray_intersection(
	t_dda_state state,
	t_ray_info	ray,
	t_ray_crossing current_crossing,
	t_dimensions map_size
)
{
	double ray_length;

	if (!is_in_bounds(state.current_cell, map_size))
		return (make_invalid_intersection());
	else if (current_crossing == R_CROSS_VERTICAL)
		ray_length = state.distance_to_next_crossing.x - state.one_step_distance.x;
	else
		ray_length = state.distance_to_next_crossing.y - state.one_step_distance.y;
	return (t_ray_intersection){
		.point = state.current_cell,
		.crossing = current_crossing,
		.ray_length = ray_length,
		.ray_direction = ray.direction,
		.axis_direction = ray.axis_direction
	};
}