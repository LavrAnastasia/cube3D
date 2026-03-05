#include "raycast.h"
#include "raycast_internal.h"
#include "map.h" // TODO:  map[map_y][map_x] != TILE_WALL -- is_inbounds and is_wall shoul bw helpers

static t_axis_direction	calc_axis_direction(double ray_direction_x, double ray_direction_y)
{
    const double eps = 1e-9;
	t_axis_direction	direction;

    direction.x = X_NONE;
    direction.y = Y_NONE;
	if (ray_direction_x < -eps)
        direction.x = X_LEFT;
    else if (ray_direction_x > eps)
        direction.x = X_RIGHT;  
    if (ray_direction_y < -eps)
        direction.y = Y_TOP;
    else if (ray_direction_y > eps)
        direction.y = Y_BOTTOM; 
	return (direction);
}

static double ray_delta_distance(double ray_direction_value)
{
    const double eps = 1e-9;

    if (fabs(ray_direction_value) < eps)
        return DBL_MAX;
    return fabs(1.0 / ray_direction_value);
}

static int	is_in_bounds(t_point point, t_dimensions size)
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
    const t_vector ray_direction = (t_vector){.x = cos(angle), .y = sin(angle)};
    const t_axis_direction axis_direction = calc_axis_direction(ray_direction.x, ray_direction.y);
    const double delta_dist_x = ray_delta_distance(ray_direction.x);
    const double delta_dist_y = ray_delta_distance(ray_direction.y);

    int map_x = (int)floor(player_pos.x);
    int map_y = (int)floor(player_pos.y);

    double side_dist_x = DBL_MAX;
    double side_dist_y = DBL_MAX;

    if (axis_direction.x == X_RIGHT)
        side_dist_x = (map_x + 1.0 - player_pos.x) * delta_dist_x;
    else if (axis_direction.x == X_LEFT)
        side_dist_x = (player_pos.x - map_x) * delta_dist_x;
    if (axis_direction.y == Y_BOTTOM)
        side_dist_y = (map_y + 1.0 - player_pos.y) * delta_dist_y;
    else if (axis_direction.y == Y_TOP)
        side_dist_y = (player_pos.y - map_y) * delta_dist_y;

    // TODO: separate above and below

    t_ray_crossing crossing = R_CROSS_VERTICAL; 
    t_point point = (t_point){ .x = map_x, .y = map_y };
    if (axis_direction.x == X_NONE && axis_direction.y == Y_NONE)
    {
        return (t_ray_intersection){
            .point = point,
            .crossing = R_CROSS_VERTICAL,
            .ray_length = DBL_MAX,
            .ray_direction = ray_direction,
            .axis_direction = axis_direction
        };
    }
    int step_x;
    int step_y;

    step_x = 0;
    if (axis_direction.x == X_RIGHT)
        step_x = 1;
    else if (axis_direction.x == X_LEFT)
        step_x = -1;

    step_y = 0;
    if (axis_direction.y == Y_TOP)
        step_y = -1;
    else if (axis_direction.y == Y_BOTTOM)
        step_y = 1;

    while (is_in_bounds(point, map_size) && !is_wall(map[point.y][point.x])) 
    {
        if (step_y == 0 || (step_x != 0 && side_dist_x < side_dist_y))
        {
            crossing = R_CROSS_VERTICAL;
            side_dist_x += delta_dist_x;
            point.x += step_x;
        }
        else
        {
            crossing = R_CROSS_HORIZONTAL;
            side_dist_y += delta_dist_y;
            point.y += step_y;
        }
    }

    double ray_length;

    if (!is_in_bounds(point, map_size))
        ray_length = DBL_MAX;
    else if (crossing == R_CROSS_VERTICAL)
        ray_length = side_dist_x - delta_dist_x;
    else
        ray_length = side_dist_y - delta_dist_y;

    // TODO: add ray direction
    return (t_ray_intersection){
        .point = point,
        .crossing = crossing,
        .ray_length = ray_length,
        .ray_direction = ray_direction,
        .axis_direction = axis_direction
    };
}