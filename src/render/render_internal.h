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

typedef struct s_column_segments
{
	t_range	ceiling;
	t_range	wall;
	t_range	floor;
}	t_column_segments;

#endif