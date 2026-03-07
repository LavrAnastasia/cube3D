#include "render.h"
#include "render_internal.h"

static void render_vertical_segment(t_range range, size_t x, t_px_buffer *buffer, int color)
{
	size_t y;

	y = range.start;
	while (y < range.end)
	{
		pixels_put(buffer, x, y, color);
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

static t_position calc_hit_position(t_position player_pos, double ray_length, t_vector ray_direction)
{
	return (t_position){
		.x = player_pos.x + ray_length * ray_direction.x,
		.y = player_pos.y + ray_length * ray_direction.y
	};
}	

static int clamp(int value, int min, int max)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}

static double calc_position_along_wall(t_position hit_position, t_ray_crossing crossing)
{
	double position_along_wall;

	if (crossing == R_CROSS_VERTICAL)
		position_along_wall = (hit_position.y - floor(hit_position.y));
	else
		position_along_wall = (hit_position.x - floor(hit_position.x));	
	return (position_along_wall);
}

static t_image_buffer *select_wall_texture(t_ray_intersection ray_intersection, t_textures *textures)
{
	t_image_buffer *wall_texture;

	wall_texture = NULL;
	if (ray_intersection.crossing == R_CROSS_VERTICAL)
	{
		if (ray_intersection.axis_direction.x == X_LEFT)
			wall_texture = &textures->wall.west;
		else if (ray_intersection.axis_direction.x == X_RIGHT)
			wall_texture = &textures->wall.east;
	}
	else
	{
		if (ray_intersection.axis_direction.y == Y_TOP)
			wall_texture = &textures->wall.north;
		else if (ray_intersection.axis_direction.y == Y_BOTTOM)
			wall_texture = &textures->wall.south;
	}
	return (wall_texture);
}

void render(t_scene *scene, t_dimensions window_size, t_px_buffer *buffer, t_textures *textures)
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
		ray_angle = normalize_angle(scene->player.angle +  atan(camera_x * scale));
		ray_intersection = ray_dda(ray_angle,
			scene->player.pos,
			scene->map,
			scene->map_size
		);

		if (ray_intersection.ray_length == DBL_MAX) {
			render_vertical_segment(
				(t_range){.start = 0, .end = (size_t)window_size.height},
				x, buffer, scene->palette.ceiling);
			// TODO: trigger warning
			x++;
			continue;
		}

		double perp_distance = correct_fisheye_distance(ray_intersection.ray_length, ray_angle - scene->player.angle);
		t_wall_bounds wall_bounds = calc_wall_bounds(perp_distance, window_size, scale);
		
		render_vertical_segment(
			(t_range){.start = 0, .end = wall_bounds.top},
			x, buffer, scene->palette.ceiling);

		render_vertical_segment(
			(t_range){.start = wall_bounds.bottom, .end = (size_t)window_size.height},
			x, buffer, scene->palette.floor);

		const double wall_height = wall_bounds.bottom - wall_bounds.top;

		// TODO: trigger a warning
		if (wall_bounds.bottom <= wall_bounds.top)
		{
			render_vertical_segment(
				(t_range){.start = wall_bounds.top, .end = wall_bounds.bottom},
				x, buffer, scene->palette.ceiling);
			x++;
			continue;
		}

		const t_position hit_position = calc_hit_position(
			scene->player.pos, ray_intersection.ray_length, ray_intersection.ray_direction);

		const double position_along_wall = calc_position_along_wall(hit_position, ray_intersection.crossing);
		const t_image_buffer *wall_texture = select_wall_texture(ray_intersection, textures);
		
		// TODO: trigger a warning
		if (wall_texture == NULL)
		{
			render_vertical_segment(
				(t_range){.start = wall_bounds.top, .end = wall_bounds.bottom},
				x, buffer, scene->palette.ceiling);
			x++;
			continue;
		}

		// INIT TEXTURE

		int texture_x;

		texture_x = (int)floor(position_along_wall * wall_texture->size.width);
		if ((ray_intersection.crossing == R_CROSS_VERTICAL && ray_intersection.axis_direction.x == X_RIGHT)
			|| (ray_intersection.crossing == R_CROSS_HORIZONTAL && ray_intersection.axis_direction.y == Y_BOTTOM)
		)
		{
			texture_x = wall_texture->size.width - 1 - texture_x;  // TODO: check!!! flip moment
		}

		texture_x = clamp(texture_x, 0, wall_texture->size.width - 1);

		// TODO: position type?
		
		double position_down_wall;
		
		// TODO: point type ?
		int texture_y;

		size_t y;

		y = wall_bounds.top;
		while (y < wall_bounds.bottom)
		{
			position_down_wall = (double)(y - wall_bounds.top) / wall_height;
			texture_y = (int)floor(position_down_wall * wall_texture->size.height);

			texture_y = clamp(texture_y, 0, wall_texture->size.height - 1);

			int color = pixels_get(&wall_texture->px, texture_x, texture_y);
			pixels_put(buffer, x, y, color);
			y++;
		}
		x++;
	}
}