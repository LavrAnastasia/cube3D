#ifndef RAYCAST_H
# define RAYCAST_H

# include <math.h>
# include <float.h>

typedef enum e_ray_x_direction
{
	R_X_LEFT,
	R_X_RIGHT,
    R_X_NONE
}	t_ray_x_direction;

typedef enum e_ray_y_direction
{
    R_Y_TOP,
    R_Y_BOTTOM,
    R_Y_NONE
}	t_ray_y_direction;

typedef struct s_ray_direction {
    t_ray_x_direction x;
    t_ray_y_direction y;
} t_ray_direction;

typedef enum e_ray_crossing
{
	R_CROSS_VERTICAL,
	R_CROSS_HORIZONTAL 
}	t_ray_crossing;

void ray_dda(double angle, double player_x, double player_y, char **map);

#endif

