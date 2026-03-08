#include "render_internal.h"

t_position calc_hit_position(t_position player_pos, double ray_length, t_vector ray_direction)
{
	return (t_position){
		.x = player_pos.x + ray_length * ray_direction.x,
		.y = player_pos.y + ray_length * ray_direction.y
	};
}

static double correct_fisheye_distance(double ray_length, double angle_diff)
{
	const double perp_distance = ray_length * cos(angle_diff);
	
	if (perp_distance < EPS_DIST)
		return (EPS_DIST);
	return (perp_distance);
}

static t_range calc_wall_range(double distance, t_dimensions window_size, double scale)
{
	const double wall_height = (((double)window_size.width * 0.5) / scale) / distance;
	double top;
	double bottom;

	top = (window_size.height / 2.0) - (wall_height / 2.0);
	bottom = top + wall_height;
	if (top < 0)
		top = 0;
	if (bottom > (double)window_size.height)
		bottom = window_size.height;
	return (t_range){.start = (size_t)top, .end = (size_t)bottom};
}

t_range calc_wall_range_for_ray(double ray_length, double angle_diff, t_dimensions window_size, double scale)
{
    const double perp_distance = correct_fisheye_distance(ray_length, angle_diff);

	return (calc_wall_range(perp_distance, window_size, scale));
}