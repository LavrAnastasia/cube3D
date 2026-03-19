/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:16:23 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/19 15:52:00 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"
#include "scene.h"
#include "reporter.h"
#include "render_error.h"

static t_column_ray	cast_column_ray(
						size_t x,
						t_dimensions window_size,
						const t_scene *scene);
static void			render_missed_column(
						size_t x,
						size_t window_height,
						t_px_buffer *buffer,
						t_color color);

void	render_scene(
	const t_scene *scene,
	t_dimensions window_size,
	t_px_buffer *buffer,
	const t_textures *textures)
{
	size_t			x;
	t_column_ray	ray;
	t_wall_column	wall_column;

	x = 0;
	while (x < (size_t)window_size.width)
	{
		ray = cast_column_ray(x, window_size, scene);
		if (ray.intersection.ray_length == DBL_MAX)
		{
			render_missed_column(x, window_size.height, buffer,
				scene->palette.ceiling);
			x++;
			continue ;
		}
		wall_column = (t_wall_column){.x = x, .projection
			= build_wall_projection(ray.intersection.ray_length, ray.angle
				- scene->player.angle, window_size, scene->camera.scale),
			.sample = build_wall_sample(ray.intersection, textures,
				scene->player.pos), .fallback_color = scene->palette.ceiling};
		render_ceiling_and_floor(wall_column, (size_t)window_size.height,
			buffer, &scene->palette);
		render_wall(wall_column, buffer);
		x++;
	}
}

static t_column_ray	cast_column_ray(
	size_t x,
	t_dimensions window_size,
	const t_scene *scene)
{
	const double	scale = scene->camera.scale;
	const double	camera_x = 2.0 * ((double)x + 0.5)
		/ (double)window_size.width - 1.0;
	const double	angle = normalize_angle(scene->player.angle
			+ atan(camera_x * scale));

	return ((t_column_ray){.angle = angle, .intersection = ray_dda(angle,
			scene->player.pos, scene->map, scene->map_size)});
}

static void	render_missed_column(size_t x, size_t window_height,
		t_px_buffer *buffer, t_color color)
{
	report(D_RENDER, RENDER_ERR_RAY_INTERSECTION, SL_WARNING);
	render_vertical_segment((t_range){.start = 0, .end = window_height}, x,
		buffer, color);
}
