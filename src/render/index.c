#include "render.h"
#include <stdlib.h> // TODO: bc of size_t

void render(t_scene *scene, size_t window_width)
{
	const double fov = scene->camera.fov;
	const double view_left_angle = scene->player.angle - fov / 2.0;
	const double angle_step = fov / (double)window_width;
	double ray_angle;
	size_t x;
	t_ray_intersection ray_intersection;

	// TODO: use atan
	x = 0;
	while (x < window_width)
	{
		ray_angle = normalize_angle(
			view_left_angle
			+ ((double)x + 0.5) * angle_step);
		ray_intersection = ray_dda(ray_angle,
			scene->player.pos,
			scene->map,
			(t_dimensions){ .width = scene->map_meta.width, .height =  scene->map_meta.height }
		);

		// TODO: render column here
		(void)ray_intersection;

		x += 1;
	}
}