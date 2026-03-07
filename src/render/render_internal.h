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

typedef struct s_column_segment
{
	size_t	x;
	t_range	y_range;
} t_column_segment;

typedef struct s_wall_sample
{
	const t_image_buffer	*texture;
	int						texture_x;
}	t_wall_sample;

typedef struct s_frame
{
	t_px_buffer		*buffer;
	t_dimensions	window_size;
}	t_frame;

t_wall_sample	build_wall_sample(t_ray_intersection ray_intersection, const t_textures *textures, t_position player_pos);
int				clamp(int value, int min, int max);
t_position		calc_hit_position(t_position player_pos, double ray_length, t_vector ray_direction);
t_range			calc_wall_range_for_ray(double ray_length, double angle_diff, t_dimensions window_size, double scale);
void			render_ceiling_and_floor(t_column_segment ceiling, t_column_segment floor, t_px_buffer *buffer, t_palette *palette);
void			render_wall(t_column_segment wall_column, t_wall_sample wall_sample, t_px_buffer *buffer, t_color fallback_color);
void			render_vertical_segment(t_range range, size_t x, t_px_buffer *buffer, int color);

#endif