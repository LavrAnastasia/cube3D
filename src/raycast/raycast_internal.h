#ifndef RAYCAST_INTERNAL_H
# define RAYCAST_INTERNAL_H

# include <math.h>
# include <float.h>

typedef enum e_axis_x_direction
{
	X_LEFT,
	X_RIGHT,
	X_NONE
}	t_axis_x_direction;

typedef enum e_axis_y_direction
{
	Y_TOP,
	Y_BOTTOM,
	Y_NONE
}	t_axis_y_direction;

typedef struct s_axis_direction {
	t_axis_x_direction x;
	t_axis_y_direction y;
} t_axis_direction;

#endif