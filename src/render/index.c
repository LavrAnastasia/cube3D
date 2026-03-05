#include "render.h"
#include "render_internal.h"

static void render_vertical_segment(t_range range, size_t x, t_px_buffer *buffer, int color)
{
	size_t y;

	y = range.start;
	while (y < range.end)
	{
		put_pixel(buffer, x, y, color);
		y++;
	}	
}

static double correct_fisheye_distance(double ray_length, double angle_diff)
{
	const double perp_distance = ray_length * cos(angle_diff);
	
	if (perp_distance < EPS_DIST)
		return (EPS_DIST);
	return (perp_distance);
}

static t_wall_bounds calc_wall_bounds(double distance, t_dimensions window_size, double scale)
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
	return (t_wall_bounds){.top = (size_t)top, .bottom = (size_t)bottom};
}

void render(t_scene *scene, t_dimensions window_size, t_px_buffer *buffer)
{
	const double scale = scene->camera.scale;
	double camera_x;
	double ray_angle;
	size_t x;
	t_ray_intersection ray_intersection;

	x = 0;
	while (x < (size_t)window_size.width)
	{
		camera_x = 2.0 * ((double)x + 0.5) / (double)window_size.width - 1.0;
		ray_angle = normalize_angle(
			scene->player.angle +  atan(camera_x * scale));

		// TODO: ray_length is MAX — draw celling and print warning
		ray_intersection = ray_dda(ray_angle,
			scene->player.pos,
			scene->map,
			scene->map_size
		);

		double perp_distance = correct_fisheye_distance(ray_intersection.ray_length, ray_angle - scene->player.angle);
		t_wall_bounds wall_bounds = calc_wall_bounds(perp_distance, window_size, scale);
		
		render_vertical_segment(
			(t_range){.start = 0, .end = wall_bounds.top},
			x, buffer, scene->palette.ceiling);

		// TODO: RENDER WALL

		render_vertical_segment(
			(t_range){.start = wall_bounds.bottom, .end = (size_t)window_size.height},
			x, buffer, scene->palette.floor);
		x += 1;
	}
}