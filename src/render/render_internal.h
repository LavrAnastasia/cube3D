/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:16:32 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/16 12:16:33 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_INTERNAL_H
# define RENDER_INTERNAL_H

#include <stddef.h>
#include <float.h>

# include "math_u.h"
# include "pixels.h"
# include "raycast.h"
# include "textures.h"
# include "scene.h"

#define EPS_DIST 1e-6

typedef struct s_range
{
	size_t	start;
	size_t	end;
}	t_range;

typedef struct s_wall_projection
{
	t_range	range;
	double	top;
	double	height;
}	t_wall_projection;

typedef struct s_wall_sample
{
	const t_image_buffer	*texture;
	int						texture_x;
}	t_wall_sample;

typedef struct s_wall_column
{
	size_t				x;
	t_wall_projection	projection;
	t_wall_sample		sample;
	t_color				fallback_color;
}	t_wall_column;

typedef struct s_column_ray
{
	double				angle;
	t_ray_intersection	intersection;
}	t_column_ray;

t_wall_sample	build_wall_sample(t_ray_intersection ray_intersection, const t_textures *textures, t_position player_pos);
int				clamp(int value, int min, int max);
t_position		calc_hit_position(t_position player_pos, double ray_length, t_vector ray_direction);
t_wall_projection	build_wall_projection(double ray_length, double angle_diff, t_dimensions window_size, double scale);
void			render_ceiling_and_floor(t_wall_column wall_column, size_t window_height, t_px_buffer *buffer, const t_palette *palette);
void			render_wall(t_wall_column wall_column, t_px_buffer *buffer);
void			render_vertical_segment(t_range range, size_t x, t_px_buffer *buffer, int color);

#endif
