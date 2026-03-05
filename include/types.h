#ifndef TYPES_H
# define TYPES_H

typedef unsigned int t_color;

typedef struct s_position
{
	double	x;
	double	y;
}	t_position;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_dimensions
{
	int	width;
	int	height;
}	t_dimensions;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

#endif