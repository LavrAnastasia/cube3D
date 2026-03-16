#include "raycast_internal.h"

static t_axis_distance calc_distance_to_first_crossing(
	t_axis_direction axis_direction,
	t_position start_position,
	t_axis_distance step_distance
);
static double calc_one_step_distance(double ray_direction_value);
static t_cell_step make_cell_step(t_ray_info ray);

t_dda_state make_initial_dda_state(t_ray_info ray, t_position start_position)
{
	const t_axis_distance one_step_distance = (t_axis_distance) {
		.x = calc_one_step_distance(ray.direction.x),
		.y = calc_one_step_distance(ray.direction.y)
	};
	const t_axis_distance distance_to_next_crossing = calc_distance_to_first_crossing(
		ray.axis_direction,
		start_position,
		one_step_distance
	);

	return (t_dda_state) {
		.current_cell = (t_point){ .x = (int)floor(start_position.x), .y = (int)floor(start_position.y) },
		.distance_to_next_crossing = distance_to_next_crossing,
		.one_step_distance = one_step_distance,
		.step = make_cell_step(ray)
	};
}

static t_axis_distance calc_distance_to_first_crossing(
	t_axis_direction axis_direction,
	t_position start_position,
	t_axis_distance step_distance
)
{
	t_axis_distance distance;
	t_point start_point = (t_point) {
		.x = (int)floor(start_position.x),
		.y = (int)floor(start_position.y) };

	distance.x = DBL_MAX;
	distance.y = DBL_MAX;
	if (axis_direction.x == X_RIGHT)
		distance.x = (start_point.x + 1.0 - start_position.x) * step_distance.x;
	else if (axis_direction.x == X_LEFT)
		distance.x = (start_position.x - start_point.x) * step_distance.x;
	if (axis_direction.y == Y_BOTTOM)
		distance.y = (start_point.y + 1.0 - start_position.y) * step_distance.y;
	else if (axis_direction.y == Y_TOP)
		distance.y = (start_position.y - start_point.y) * step_distance.y;
	return (distance);
}

static double calc_one_step_distance(double ray_direction_value)
{
	const double eps = 1e-9;

	if (fabs(ray_direction_value) < eps)
		return DBL_MAX;
	return fabs(1.0 / ray_direction_value);
}

static t_cell_step make_cell_step(t_ray_info ray)
{
	t_cell_step step;

	step.x = 0;
	if (ray.axis_direction.x == X_RIGHT)
		step.x = 1;
	else if (ray.axis_direction.x == X_LEFT)
		step.x = -1;
	step.y = 0;
	if (ray.axis_direction.y == Y_TOP)
		step.y = -1;
	else if (ray.axis_direction.y == Y_BOTTOM)
		step.y = 1;
	return (step);
}