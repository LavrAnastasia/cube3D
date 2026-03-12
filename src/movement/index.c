#include <sys/time.h>
#include "movement_inner.h"
#include "map_utils.h"
#include "math_u.h"

static double	get_current_time_seconds(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((double)current_time.tv_sec + (double)current_time.tv_usec / 1000000.0);
}

static double	get_frame_delta_seconds(
	double current_time_seconds,
	double last_update_time_seconds
)
{
	double	frame_delta_seconds;

	if (last_update_time_seconds == 0.0)
		return (0.0);
	frame_delta_seconds = current_time_seconds - last_update_time_seconds;
	if (frame_delta_seconds < 0.0)
		return (0.0);
	if (frame_delta_seconds > 0.1)
		return (0.1);
	return (frame_delta_seconds);
}

void	update_player_angle(double frame_delta_seconds, t_scene *scene, const t_controls_state *controls)
{
	const double	rotation_speed_per_second = 1.5;
	const double	rotation_step = rotation_speed_per_second * frame_delta_seconds;
	int				turn_step;

	turn_step = 0;
	if (controls->turn_left)
		turn_step--;
	if(controls->turn_right)
		turn_step++;
	if (turn_step)
		scene->player.angle = normalize_angle(scene->player.angle + turn_step * rotation_step);
}

t_vector calc_move_direction(double angle, t_move_intent move_intent)
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

t_move_intent calc_move_intent(const t_controls_state *controls)
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

void try_move_x(t_scene *scene, t_position *next_position, t_vector	move_direction, double move_distance)
{
	const double hit_radius = scene->player.hit_radius;
	const double x_position_candidate = scene->player.pos.x + move_direction.x * move_distance;
	const double x = x_position_candidate + sign(move_direction.x) * hit_radius; // TODO: sign??
	const t_point point_top = (t_point){
		.x = (int)floor(x),
		.y = (int)floor(next_position->y - hit_radius)
	};
	const t_point point_bottom = (t_point){
		.x = (int)floor(x),
		.y = (int)floor(next_position->y + hit_radius)
	};

	if (is_in_bounds(point_top, scene->map_size) && is_in_bounds(point_bottom, scene->map_size)
		&& !is_wall(point_top, scene->map) && !is_wall(point_bottom, scene->map))
	{
		next_position->x = x_position_candidate;
	}
}

void try_move_y(t_scene *scene, t_position *next_position, t_vector	move_direction, double move_distance)
{
	const double hit_radius = scene->player.hit_radius;
	const double y_position_candidate = scene->player.pos.y + move_direction.y * move_distance;
	const double y = y_position_candidate + sign(move_direction.y) * hit_radius;
	const t_point point_left = (t_point){
		.x = (int)floor(next_position->x - hit_radius),
		.y = (int)floor(y)
	};
	const t_point point_right = (t_point){
		.x = (int)floor(next_position->x + hit_radius),
		.y = (int)floor(y)
	};

	if (is_in_bounds(point_left, scene->map_size) && is_in_bounds(point_right, scene->map_size)
		&& !is_wall(point_left, scene->map) && !is_wall(point_right, scene->map))
	{
		next_position->y = y_position_candidate;
	}
}

void	update_player_position(double frame_delta_seconds, t_scene *scene, const t_controls_state *controls)
{
	const t_move_intent	move_intent = calc_move_intent(controls);
	const t_vector		move_direction = calc_move_direction(scene->player.angle, move_intent);
	const double		move_distance = 3 * frame_delta_seconds; // TODO: rename 3 constant
	t_position			next_position;

	if (move_direction.x == 0.0 && move_direction.y == 0.0)
    	return;

	next_position = scene->player.pos;
	try_move_x(scene, &next_position, move_direction, move_distance);
	try_move_y(scene, &next_position, move_direction, move_distance);
	scene->player.pos = next_position;
}


void	update_player_movement(t_scene *scene, const t_controls_state *controls)
{
	const double current_time_seconds = get_current_time_seconds();
	const double frame_delta_seconds = get_frame_delta_seconds(
		current_time_seconds,
		scene->last_update_time_seconds
	);

	scene->last_update_time_seconds = current_time_seconds;
	update_player_angle(frame_delta_seconds, scene, controls);
	update_player_position(frame_delta_seconds, scene, controls);
}