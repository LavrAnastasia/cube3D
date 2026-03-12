#include "movement_inner.h"
#include "map_utils.h"
#include "math_u.h"

static t_vector calc_move_direction(double angle, t_move_intent move_intent);
static t_move_intent calc_move_intent(const t_controls_state *controls);
static void try_move_x(t_scene *scene, t_position *next_position, t_vector	move_direction, double move_distance);
static void try_move_y(t_scene *scene, t_position *next_position, t_vector	move_direction, double move_distance);

void	update_player_position(double frame_delta_seconds, t_scene *scene, const t_controls_state *controls)
{
	const t_move_intent	move_intent = calc_move_intent(controls);
	const t_vector		move_direction = calc_move_direction(scene->player.angle, move_intent);
	const double 		move_speed_per_second = 3;
	const double		move_distance = move_speed_per_second * frame_delta_seconds;
	t_position			next_position;

	if (move_direction.x == 0.0 && move_direction.y == 0.0)
    	return;
	next_position = scene->player.pos;
	try_move_x(scene, &next_position, move_direction, move_distance);
	try_move_y(scene, &next_position, move_direction, move_distance);
	scene->player.pos = next_position;
}

static t_vector calc_move_direction(double angle, t_move_intent move_intent)
{
	const t_vector	y_direction = (t_vector){.x = cos(angle), .y = sin(angle)};
	const t_vector	x_direction = (t_vector){.x = -sin(angle), .y = cos(angle)};
	const double	eps = 1e-6;
	t_vector		move_direction;
	double			length;

	move_direction.x = move_intent.y * y_direction.x + move_intent.x * x_direction.x;
	move_direction.y = move_intent.y * y_direction.y + move_intent.x * x_direction.y;
	length = sqrt(pow(move_direction.x, 2) + pow(move_direction.y, 2));
	if (length > 0)
	{
		move_direction.x /= length; 
		move_direction.y /= length;
	}
	if (fabs(move_direction.x) < eps)
		move_direction.x = 0.0;
	if (fabs(move_direction.y) < eps)
		move_direction.y = 0.0;
	return (move_direction);
}

static t_move_intent calc_move_intent(const t_controls_state *controls)
{
	t_move_intent move_intent;

	move_intent.x = 0;
	move_intent.y = 0;
	if (controls->move_backward)
		move_intent.y--; 
	if (controls->move_forward)
		move_intent.y++; 
	if (controls->move_left)
		move_intent.x--;
	if (controls->move_right)
		move_intent.x++;
	return (move_intent);
}

static void try_move_x(t_scene *scene, t_position *next_position, t_vector	move_direction, double move_distance)
{
	const double	hit_radius = scene->player.hit_radius;
	const double	x_position_candidate = scene->player.pos.x + move_direction.x * move_distance;
	double			x;
	t_point			point_top;
	t_point			point_bottom;
	
	if (move_direction.x == 0.0)
		return;
	if (move_direction.x > 0.0)
		x = x_position_candidate + hit_radius;
	else
		x = x_position_candidate - hit_radius;
	point_top = (t_point){.x = (int)floor(x), .y = (int)floor(next_position->y - hit_radius)};
	point_bottom = (t_point){.x = (int)floor(x), .y = (int)floor(next_position->y + hit_radius)};
	if (is_in_bounds(point_top, scene->map_size) && is_in_bounds(point_bottom, scene->map_size)
		&& !is_wall(point_top, scene->map) && !is_wall(point_bottom, scene->map))
		next_position->x = x_position_candidate;
}

static void try_move_y(t_scene *scene, t_position *next_position, t_vector	move_direction, double move_distance)
{
	const double	hit_radius = scene->player.hit_radius;
	const double	y_position_candidate = scene->player.pos.y + move_direction.y * move_distance;
	double			y;
	t_point			point_left;
	t_point			point_right;
	
	if (move_direction.y == 0.0)
		return;
	if (move_direction.y > 0.0)
		y = y_position_candidate + hit_radius;
	else
		y = y_position_candidate - hit_radius;
	point_left = (t_point){.x = (int)floor(next_position->x - hit_radius), .y = (int)floor(y)};
	point_right = (t_point){.x = (int)floor(next_position->x + hit_radius), .y = (int)floor(y)};
	if (is_in_bounds(point_left, scene->map_size) && is_in_bounds(point_right, scene->map_size)
		&& !is_wall(point_left, scene->map) && !is_wall(point_right, scene->map))
		next_position->y = y_position_candidate;
}