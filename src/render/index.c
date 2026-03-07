#include "scene.h"
#include "render_internal.h"

static t_column_ray cast_column_ray(size_t x, t_dimensions window_size, t_scene *scene);
static void 		render_missed_column(size_t window_height, size_t x, t_px_buffer *buffer, t_color color);

void render_scene(t_scene *scene, t_dimensions window_size, t_px_buffer *buffer, const t_textures *textures)
{
	size_t x;
	t_column_ray ray;
	t_range wall_range;
	t_column_segment wall_column;

	x = 0;
	while (x < (size_t)window_size.width)
	{	
		ray = cast_column_ray(x, window_size, scene);
		if (ray.intersection.ray_length == DBL_MAX)
		{
			render_missed_column(window_size.height, x, buffer, scene->palette.ceiling);
			x++;
			continue;
		}
		wall_range = calc_wall_range_for_ray(ray.intersection.ray_length,
			ray.angle - scene->player.angle, window_size, scene->camera.scale);
		wall_column = (t_column_segment){ .x = x, .y_range = wall_range} ;
		render_ceiling_and_floor(wall_column, (size_t)window_size.height, buffer, &scene->palette);
		render_wall(wall_column,
			build_wall_sample(ray.intersection, textures, scene->player.pos),
			buffer, scene->palette.ceiling);
		x++;
	}
}

static t_column_ray cast_column_ray(size_t x, t_dimensions window_size, t_scene *scene)
{
	const double	scale = scene->camera.scale;
	const double	camera_x = 2.0 * ((double)x + 0.5) / (double)window_size.width - 1.0;
	const double	angle = normalize_angle(scene->player.angle +  atan(camera_x * scale));

	return ((t_column_ray){
		.angle = angle,
		.intersection = ray_dda(angle, scene->player.pos, scene->map, scene->map_size)
	});
}

static void render_missed_column(size_t window_height, size_t x, t_px_buffer *buffer, t_color color)
{
	render_vertical_segment((t_range){.start = 0, .end = window_height}, x, buffer, color);
	// TODO: warning
}
