#ifndef RENDER_INTERNAL_H
# define RENDER_INTERNAL_H

#include <stddef.h>
#include <float.h>

# include "math_u.h"
# include "pixels.h"
# include "raycast.h"

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

#endif