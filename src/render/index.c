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

static const t_image_buffer *select_wall_texture(t_ray_intersection ray_intersection, t_textures *textures)
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

static int calc_texture_x(double position_along_wall, t_ray_intersection ray_intersection, const t_image_buffer *texture)
{
	int texture_x;

	texture_x = (int)floor(position_along_wall * texture->size.width);
	if ((ray_intersection.crossing == R_CROSS_VERTICAL && ray_intersection.axis_direction.x == X_RIGHT)
		|| (ray_intersection.crossing == R_CROSS_HORIZONTAL && ray_intersection.axis_direction.y == Y_BOTTOM)
	)
	{
		texture_x = texture->size.width - 1 - texture_x;  // TODO: check!!! flip moment
	}

	return (clamp(texture_x, 0, texture->size.width - 1));
}

static void render_wall(t_column_segment column, t_wall_sample wall, t_px_buffer *buffer)
{
	const double	wall_height = column.y_range.end - column.y_range.start;	
	double			position_down_wall;
	int				texture_y;
	size_t			y;
	int				color;

	y = column.y_range.start;
	while (y < column.y_range.end)
	{
		position_down_wall = (double)(y - column.y_range.start) / wall_height;
		texture_y = (int)floor(position_down_wall * wall.texture->size.height);

		texture_y = clamp(texture_y, 0, wall.texture->size.height - 1);

		color = pixels_get(&wall.texture->px, wall.texture_x, texture_y);
		pixels_put(buffer, column.x, y, color);
		y++;
	}
}

// TODO: trigger a warning
static void render_wall_fallback(size_t x, t_px_buffer *buffer, t_range range, t_color color)
{
	render_vertical_segment(range, x, buffer, color);
}

static void render_ceiling_and_floor(t_column_segment ceiling, t_column_segment floor, t_px_buffer *buffer, t_palette *palette)
{
	render_vertical_segment(ceiling.y_range, ceiling.x, buffer, palette->ceiling);
	render_vertical_segment(floor.y_range, floor.x, buffer, palette->floor);
}

static t_wall_sample build_wall_sample(t_ray_intersection ray_intersection, t_textures *textures, t_position player_pos)
{
	const t_image_buffer *wall_texture = select_wall_texture(ray_intersection, textures);
	const t_position hit_position = calc_hit_position(player_pos, ray_intersection.ray_length, ray_intersection.ray_direction);
	const double position_along_wall = calc_position_along_wall(hit_position, ray_intersection.crossing);

	if (wall_texture == NULL)
		return (t_wall_sample){ .texture =wall_texture, .texture_x = 0 };

	return (t_wall_sample){
		.texture = wall_texture,
		.texture_x = calc_texture_x(
			position_along_wall,
			ray_intersection,
			wall_texture)
	};
}

static void render_wall_segment(t_column_segment wall_column, t_wall_sample wall_sample, t_px_buffer *buffer, t_color fallback_color) {
	if (wall_column.y_range.end <= wall_column.y_range.start) {
		render_wall_fallback(wall_column.x, buffer, wall_column.y_range, fallback_color);
		return;
	}
	
	if (wall_sample.texture == NULL) {
		render_wall_fallback(wall_column.x, buffer, wall_column.y_range, fallback_color);
		return;
	}
	
	render_wall(wall_column, wall_sample, buffer);
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
			x++;
			continue;
		}

		double perp_distance = correct_fisheye_distance(ray_intersection.ray_length, ray_angle - scene->player.angle);
		t_range wall_range = calc_wall_range(perp_distance, window_size, scale);

		render_ceiling_and_floor(
			(t_column_segment){.x = x, .y_range = (t_range){.start = 0, .end = wall_range.start}},
			(t_column_segment){.x = x, .y_range = (t_range){.start = wall_range.end, .end = (size_t)window_size.height}},
			buffer, &scene->palette
		);

		render_wall_segment(
			(t_column_segment){.x = x, .y_range = wall_range},
			build_wall_sample(ray_intersection, textures, scene->player.pos),
			buffer,
			scene->palette.ceiling
		);

		x++;
	}
}
