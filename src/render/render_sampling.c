/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sampling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:16:41 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/16 12:36:51 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

static const t_image_buffer	*select_wall_texture(
								t_ray_intersection ray_intersection,
								const t_textures *textures);
static double				calc_position_along_wall(
								t_position hit_position,
								t_ray_crossing crossing);
static int					calc_texture_x(
								double position_along_wall,
								t_ray_intersection ray_intersection,
								const t_image_buffer *texture);

t_wall_sample	build_wall_sample(
	t_ray_intersection ray_intersection,
	const t_textures *textures,
	t_position player_pos)
{
	t_position				hit_position;
	double					position_along_wall;
	const t_image_buffer	*wall_texture = select_wall_texture(
			ray_intersection, textures);

	if (wall_texture == NULL)
		return ((t_wall_sample){.texture = wall_texture, .texture_x = 0});
	hit_position = calc_hit_position(player_pos, ray_intersection.ray_length,
			ray_intersection.ray_direction);
	position_along_wall = calc_position_along_wall(hit_position,
			ray_intersection.crossing);
	return ((t_wall_sample){.texture = wall_texture,
		.texture_x = calc_texture_x(position_along_wall, ray_intersection,
			wall_texture)});
}

static int	calc_texture_x(
	double position_along_wall,
	t_ray_intersection ray_intersection,
	const t_image_buffer *texture)
{
	int	texture_x;

	texture_x = (int)floor(position_along_wall * texture->size.width);
	if ((ray_intersection.crossing == R_CROSS_VERTICAL
			&& ray_intersection.axis_direction.x == X_RIGHT)
		|| (ray_intersection.crossing == R_CROSS_HORIZONTAL
			&& ray_intersection.axis_direction.y == Y_BOTTOM))
	{
		texture_x = texture->size.width - 1 - texture_x;
			// TODO: check!!! flip moment
	}
	return (clamp(texture_x, 0, texture->size.width - 1));
}

static double	calc_position_along_wall(
	t_position hit_position,
	t_ray_crossing crossing)
{
	double	position_along_wall;

	if (crossing == R_CROSS_VERTICAL)
		position_along_wall = (hit_position.y - floor(hit_position.y));
	else
		position_along_wall = (hit_position.x - floor(hit_position.x));
	return (position_along_wall);
}

static const t_image_buffer	*select_wall_texture(
	t_ray_intersection ray_intersection,
	const t_textures *textures)
{
	const t_image_buffer	*wall_texture;

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
