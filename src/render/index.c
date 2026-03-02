#include "render.h"


void render(t_scene *scene, t_dimensions window_size)
{
	const double scale = scene->camera.scale;
	double cameraX;
	double ray_angle;
	size_t x;
	t_ray_intersection ray_intersection;

	x = 0;
	while (x < (size_t)window_size.width)
	{
		cameraX = 2.0 * ((double)x + 0.5) / (double)window_size.width - 1.0;
		ray_angle = normalize_angle(
			scene->player.angle +  atan(cameraX * scale));
		ray_intersection = ray_dda(ray_angle,
			scene->player.pos,
			scene->map,
			(t_dimensions){ .width = scene->map_meta.width,
				.height =  scene->map_meta.height }
		);

		(void) ray_intersection;
		x += 1;
	}
}