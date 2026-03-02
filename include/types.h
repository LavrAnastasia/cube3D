#ifndef TYPES_H
# define TYPES_H

#include <stdlib.h> // TODO: bc of size_t

typedef struct s_position
{
	double	x;
	double	y;
}	t_position;

typedef struct s_cell
{
	int	x;
	int	y;
}	t_cell;

typedef struct s_dimensions
{
	int	width;
	int	height;
}	t_dimensions;

#endif