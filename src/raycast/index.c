#include "raycast.h"
#include "map.h"

t_ray_direction	ray_direction(double cx, double sy)
{
    const double eps = 1e-9;
	t_ray_direction	direction;

    direction.x = R_X_NONE;
    direction.y = R_Y_NONE;
	if (cx < -eps)
        direction.x = R_X_LEFT;
    else if (cx > eps)
        direction.x = R_X_RIGHT;  
    if (sy < -eps)
        direction.y = R_Y_TOP;
    else if (sy > eps)
        direction.y = R_Y_BOTTOM; 
	return (direction);
}

double ray_delta_direction(double ray_direction_value)
{
    const double eps = 1e-9;

    if (fabs(ray_direction_value) < eps)
        return DBL_MAX;
    return fabs(1.0 / ray_direction_value);
}

static int	is_in_bounds(t_position point, t_position size)
{
	return (
		point.x >= 0 && point.x < size.x
		&& point.y >= 0 && point.y < size.y
	);
}

void ray_dda(double angle, double player_x, double player_y, char **map)
{
    const double cx = cos(angle);
    const double sy = sin(angle);
    const t_ray_direction direction = ray_direction(cx, sy);
    const double delta_dist_x = ray_delta_direction(cx);
    const double delta_dist_y = ray_delta_direction(sy);

    int map_x = (int)floor(player_x);
    int map_y = (int)floor(player_y);

    double side_dist_x = DBL_MAX;
    double side_dist_y = DBL_MAX;

    if (direction.x == R_X_RIGHT)
        side_dist_x = (map_x + 1.0 - player_x) * delta_dist_x;
    else if (direction.x == R_X_LEFT)
        side_dist_x = (player_x - map_x) * delta_dist_x;
    if (direction.y == R_Y_BOTTOM)
        side_dist_y = (map_y + 1.0 - player_y) * delta_dist_y;
    else if (direction.y == R_Y_TOP)
        side_dist_y = (player_y - map_y) * delta_dist_y;

    t_ray_crossing crossing = R_CROSS_VERTICAL; 

    t_position map_size = (t_position){ .x = 10, .y = 10 }; // TODO: use real map size
    t_position cell = (t_position){ .x = map_x, .y = map_y };
    while (is_in_bounds(cell, map_size) && map[map_y][map_x] != TILE_WALL) 
    {
        if (side_dist_x < side_dist_y)
        {
            crossing = R_CROSS_VERTICAL;
            side_dist_x += delta_dist_x;
            if (direction.x == R_X_RIGHT)
                map_x += 1;
            else if (direction.x == R_X_LEFT)
                map_x -= 1;
        }
        else
        {
            crossing = R_CROSS_HORIZONTAL;
            side_dist_y += delta_dist_y;
            if (direction.y == R_Y_TOP)
                map_y -= 1;
            else if (direction.y == R_Y_BOTTOM)
                map_y += 1;
        }
        cell.x = map_x;
        cell.y = map_y;
    }

    (void)crossing;

}