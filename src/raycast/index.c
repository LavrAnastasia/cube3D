#include <stdbool.h>
#include "raycast_internal.h"
#include "map_utils.h"

static bool is_valid_ray(t_ray_info	ray);
static bool is_valid_start_cell(t_point point, char **map, t_dimensions map_size);
static bool should_take_x_step(t_dda_state state);
static void update_dda_state(t_ray_crossing crossing, t_dda_state *state);

t_ray_intersection ray_dda(
	double angle,
	t_position player_pos,
	char **map,
	t_dimensions map_size
)
{
	const t_ray_info	ray = make_ray_info(angle);
	const t_map			map_ctx = {.map = map, .map_size = map_size};
	t_dda_state			state;
	t_ray_crossing		current_crossing;
	
	if (!is_valid_ray(ray))
		return (make_invalid_intersection());
	state = make_initial_dda_state(ray, player_pos);
	if (!is_valid_start_cell(state.current_cell, map, map_size))
		return (make_invalid_intersection());
	while (is_in_bounds(state.current_cell, map, map_size) && !is_wall(state.current_cell, map)) 
	{
		if (should_take_x_step(state))
			current_crossing = R_CROSS_VERTICAL;
		else
			current_crossing = R_CROSS_HORIZONTAL;
		update_dda_state(current_crossing, &state);
	}
	return (make_ray_intersection(state, ray, current_crossing, map_ctx));
}

static void update_dda_state(t_ray_crossing crossing, t_dda_state *state)
{
	if (crossing == R_CROSS_VERTICAL)
	{
		state->distance_to_next_crossing.x += state->one_step_distance.x;
		state->current_cell.x += state->step.x;
	}
	else
	{
		state->distance_to_next_crossing.y += state->one_step_distance.y;
		state->current_cell.y += state->step.y;
	}
}

static bool is_valid_ray(t_ray_info	ray)
{
	return (ray.axis_direction.x != X_NONE || ray.axis_direction.y != Y_NONE);
}

static bool is_valid_start_cell(t_point point, char **map, t_dimensions map_size)
{
	return (is_in_bounds(point, map, map_size) && !is_wall(point, map));
}

static bool should_take_x_step(t_dda_state state)
{
	return (state.step.y == 0
		|| (state.step.x != 0
			&& state.distance_to_next_crossing.x < state.distance_to_next_crossing.y));
}
