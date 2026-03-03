#include "raycast.h"
#include "map.h" // TODO:  map[map_y][map_x] != TILE_WALL -- is_inbounds and is_wall shoul bw helpers
#include "types.h"

static t_ray_direction	ray_direction(double cx, double sy)
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

static double ray_delta_direction(double ray_direction_value)
{
    const double eps = 1e-9;

    if (fabs(ray_direction_value) < eps)
        return DBL_MAX;
    return fabs(1.0 / ray_direction_value);
}

static int	is_in_bounds(t_cell point, t_dimensions size)
{
	return (
		point.x >= 0 && point.x < size.width
		&& point.y >= 0 && point.y < size.height
	);
}

static int	is_wall(char tile)
{
    return (tile == TILE_WALL);
}

t_ray_intersection ray_dda(double angle, t_position player_pos, char **map, t_dimensions map_size)
{
    // TODO: setup ray
    const double cx = cos(angle);
    const double sy = sin(angle);
    const t_ray_direction direction = ray_direction(cx, sy);
    const double delta_dist_x = ray_delta_direction(cx);
    const double delta_dist_y = ray_delta_direction(sy);

    int map_x = (int)floor(player_pos.x);
    int map_y = (int)floor(player_pos.y);

    double side_dist_x = DBL_MAX;
    double side_dist_y = DBL_MAX;

    if (direction.x == R_X_RIGHT)
        side_dist_x = (map_x + 1.0 - player_pos.x) * delta_dist_x;
    else if (direction.x == R_X_LEFT)
        side_dist_x = (player_pos.x - map_x) * delta_dist_x;
    if (direction.y == R_Y_BOTTOM)
        side_dist_y = (map_y + 1.0 - player_pos.y) * delta_dist_y;
    else if (direction.y == R_Y_TOP)
        side_dist_y = (player_pos.y - map_y) * delta_dist_y;

    // TODO: separate above and below

    t_ray_crossing crossing = R_CROSS_VERTICAL; 
    t_cell cell = (t_cell){ .x = map_x, .y = map_y };
    if (direction.x == R_X_NONE && direction.y == R_Y_NONE)
    {
        return (t_ray_intersection){
            .cell = cell,
            .crossing = R_CROSS_VERTICAL,
            .distance = DBL_MAX
        };
    }
    int step_x;
    int step_y;

    step_x = 0;
    if (direction.x == R_X_RIGHT)
        step_x = 1;
    else if (direction.x == R_X_LEFT)
        step_x = -1;

    step_y = 0;
    if (direction.y == R_Y_TOP)
        step_y = -1;
    else if (direction.y == R_Y_BOTTOM)
        step_y = 1;

    while (is_in_bounds(cell, map_size) && !is_wall(map[cell.y][cell.x])) 
    {
        if (step_y == 0 || (step_x != 0 && side_dist_x < side_dist_y))
        {
            crossing = R_CROSS_VERTICAL;
            side_dist_x += delta_dist_x;
            cell.x += step_x;
        }
        else
        {
            crossing = R_CROSS_HORIZONTAL;
            side_dist_y += delta_dist_y;
            cell.y += step_y;
        }
    }

    double distance;

    if (!is_in_bounds(cell, map_size))
        distance = DBL_MAX;
    else if (crossing == R_CROSS_VERTICAL)
        distance = side_dist_x - delta_dist_x;
    else
        distance = side_dist_y - delta_dist_y;

    return (t_ray_intersection){
        .cell = cell,
        .crossing = crossing,
        .distance = distance
    };
}