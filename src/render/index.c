#include "scene.h"
#include "render_internal.h"

void render_scene(t_scene *scene, t_dimensions window_size, t_px_buffer *buffer, const t_textures *textures)
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
		ray_intersection = ray_dda(ray_angle, scene->player.pos, scene->map, scene->map_size);

		if (ray_intersection.ray_length == DBL_MAX) {
			render_vertical_segment(
				(t_range){.start = 0, .end = (size_t)window_size.height},
				x, buffer, scene->palette.ceiling);
			x++;
			continue;
		}

		t_range wall_range = calc_wall_range_for_ray(
			ray_intersection.ray_length,
			ray_angle - scene->player.angle,
			window_size, scale
		);

		render_ceiling_and_floor(
			(t_column_segment){.x = x, .y_range = (t_range){.start = 0, .end = wall_range.start}},
			(t_column_segment){.x = x, .y_range = (t_range){.start = wall_range.end, .end = (size_t)window_size.height}},
			buffer, &scene->palette
		);

		render_wall(
			(t_column_segment){.x = x, .y_range = wall_range},
			build_wall_sample(ray_intersection, textures, scene->player.pos),
			buffer,
			scene->palette.ceiling
		);

		x++;
	}
}
